#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <byteswap.h>
#include <unistd.h>

#include <iostream>
using namespace std;

struct Buffer {
    bool m_needMore;
    char *m_addr;
    ssize_t m_size;
    ssize_t m_pos;
    Buffer() : m_addr(NULL), m_size(0), m_pos(0), m_needMore(true)  {}
};

struct Block {
    Block() : m_sp(0), m_len(0) {}
    size_t m_sp;
    uint16_t m_len;
    void skipToEnd(Buffer &b) {
        b.m_pos = m_sp + m_len;
    }
};

struct Header : Block {
    uint16_t m_updates;
    Header() : Block(), m_updates(0) {}
    void parseAndCheck(Buffer &b) {
	m_sp = b.m_pos;
	size_t ep = m_sp + sizeof(m_len) + sizeof(m_updates);
        b.m_needMore = (ep > b.m_size);
	if (b.m_needMore)
	    return;
	char *addr = &b.m_addr[m_sp];
        m_len = bswap_16(*(uint16_t*)addr);
	addr += sizeof(m_len);
        m_updates = bswap_16(*(uint16_t*)addr);
	addr += sizeof(m_updates);
	b.m_needMore = (m_sp + m_len) > b.m_size;
	if (b.m_needMore) 
	    return;
	b.m_pos = ep;
    }
};

struct Common : Block {
    char m_type;
    char m_symbol[6];
    void parse(Buffer &b) {
	m_sp = b.m_pos;
	char *addr = &b.m_addr[b.m_pos];
        m_len = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_len);
        m_type = *addr;
        addr += sizeof(m_type);
	ssize_t n = sizeof(m_symbol) - 1;
        memcpy(m_symbol, addr, n);
	m_symbol[n] = '\0';
        addr += n;
	b.m_pos = addr - b.m_addr;
    }
};

struct Quote {
    uint16_t m_pl;
    uint16_t m_pls;
    uint64_t m_plp;
    void parse(Buffer &b) {
        char *addr = &b.m_addr[b.m_pos];
        m_pl = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_pl);
        m_pls = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_pls);
        m_plp = bswap_64(*(uint64_t*)addr);
        addr += sizeof(m_plp);
        b.m_pos = addr - b.m_addr;
    }

};

struct Trade {
    uint16_t m_ts;
    uint64_t m_tp;
    void parse(Buffer &b) {
	char *addr = &b.m_addr[b.m_pos];
        m_ts = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_ts);
        m_tp = bswap_64(*(uint64_t*)addr);
        addr += sizeof(m_tp);
	b.m_pos = addr - b.m_addr;
    }

};

class File {
    const string m_ifn;
    int m_ifd;
    size_t m_offset;
    size_t m_size;
    const size_t m_pageSize;
    const size_t m_maxReadSize;

public:
    File(const string &fn) : m_ifn(fn), m_ifd(-1), m_offset(0), m_size(0), 
	                     m_pageSize(getpagesize()),
	                     m_maxReadSize((16 + 1) * m_pageSize) {}

    ~File() {
        if (m_ifd >= 0) 
	    close(m_ifd);
    }

    bool openf()
    {
        m_ifd = open(m_ifn.c_str(), O_RDONLY);
	if (m_ifd < 0) {
	    cerr << "Can't open " << m_ifn << " file." << endl;
	    return false;
	}
	struct stat sb;
        fstat(m_ifd, &sb);
	m_size = sb.st_size;
	return true;
    }

    bool readmore(Buffer &buff) {
	if (!buff.m_needMore) 
	    return true;
	if (buff.m_addr != NULL)
            munmap(buff.m_addr, buff.m_size);
	size_t newPos = buff.m_pos % m_pageSize;
	m_offset += buff.m_pos - newPos;
	buff.m_pos = newPos;
	buff.m_size = min(m_maxReadSize, m_size - m_offset);
        if(m_offset >= m_size || buff.m_pos >= buff.m_size) { 
            cerr << "Successfully reached EOF." << endl;
            return false;
	}
	buff.m_addr = (char*)mmap(NULL, buff.m_size, PROT_READ, MAP_PRIVATE /*| MAP_HUGETLB | MAP_HUGE_2MB*/, m_ifd, m_offset);
        if (buff.m_addr == MAP_FAILED) {
            cerr << "mmap of size: " << buff.m_size << " failed at offset: " << m_offset << endl;
	    exit(-1);
	}
	buff.m_needMore = false;
	return true;
    }
};

class Record {
public:
    void print(Buffer &b, FILE *ofp) {
	Header h;
        h.parseAndCheck(b);
	if (b.m_needMore)
            return;
	for(int i(0); i < h.m_updates; ++i) {
            Common c;
	    c.parse(b);
	    switch(c.m_type) {
                case 'T':
                    Trade t;
                    t.parse(b);
		    fprintf(ofp, "%d %s @ %.2f\n", (uint64_t)t.m_ts * 100, c.m_symbol, (double)t.m_tp / 10000);
		    break;
                case 'Q':
                    Quote q;
	            q.parse(b);
		    fprintf(ofp, "%d %s @ %.2f\n", (uint64_t)q.m_pls * 100, c.m_symbol, (double)q.m_plp / 10000);
		    break;
		default:
		    cerr << "Encouneted unknown record type: " << c.m_type << endl;
		    exit(-1);
		    break;
	    }
	    c.skipToEnd(b);
	}
	h.skipToEnd(b);
    }
};

class Printer {
    File m_if;
    FILE *m_ofp;

public:
    Printer(const char* ifn, const char *ofn) : m_if(ifn) {
        m_ofp = fopen(ofn, "w");
    }

    ~Printer() {
        if (m_ofp)
	    fclose(m_ofp);
    }

    int print() {
        if (m_ofp == NULL)
	    return -1;
	Buffer b;
	if (!m_if.openf())
	    return -1;
	while(m_if.readmore(b)) {
            Record().print(b, m_ofp);
	}
        return 0;         	
    }
};

int main() {
    Printer p("./input.dat", "./output.txt");
    return p.print();
}
