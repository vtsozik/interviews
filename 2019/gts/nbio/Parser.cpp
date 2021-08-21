#include <byteswap.h>
#include <iostream>
#include <InputFile.hpp>
#include <OutputFile.hpp>
using namespace std;

template <size_t capacity> struct IOBuffer {
    static constexpr size_t scm_capacity = 2 * capacity;
    char m_buf[scm_capacity];
    size_t m_size;
    size_t m_pos;
    IOBuffer() : m_size(0), m_pos(0) {}
    void rewind()
    {
	if (m_pos > 0)
	{
	    if (m_size < m_pos)
	    {
                cerr << "Buffer overflow, current position: " << m_pos << ", buffer size: " << m_size << endl;
		exit(-1);
	    }
            m_size -= m_pos;
	    if (m_size > 0)
	    {
                memmove(m_buf, &m_buf[m_pos], m_size);
	    }
	    m_pos = 0;
	}
    }
};

struct InputBuffer : IOBuffer<Buffer::scm_capacity> {};
struct OutputBuffer : IOBuffer<Buffer::scm_capacity> {};

struct Quote {
    uint16_t m_pl;
    uint16_t m_pls;
    uint64_t m_plp;
    void parse(InputBuffer &ib) {
        char *addr = &ib.m_buf[ib.m_pos];
        m_pl = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_pl);
        m_pls = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_pls);
        m_plp = bswap_64(*(uint64_t*)addr);
        addr += sizeof(m_plp);
        ib.m_pos = addr - ib.m_buf;
    }

};

struct Trade {
    uint16_t m_ts;
    uint64_t m_tp;
    void parse(InputBuffer &ib) {
	char *addr = &ib.m_buf[ib.m_pos];
        m_ts = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_ts);
        m_tp = bswap_64(*(uint64_t*)addr);
        addr += sizeof(m_tp);
	ib.m_pos = addr - ib.m_buf;
    }

};

struct Block {
    Block() : m_sp(0), m_len(0) {}
    size_t m_sp;
    uint16_t m_len;
    void skipToEnd(InputBuffer &ib) {
        ib.m_pos = m_sp + m_len;
    }
};

struct Header : Block {
    uint16_t m_updates;
    Header() : Block(), m_updates(0) {}
    int parseAndCheck(InputBuffer &ib) {
	m_sp = ib.m_pos;
	size_t ep = m_sp + sizeof(m_len) + sizeof(m_updates);
        if (ep > ib.m_size)
	    return -ep;
	char *addr = &ib.m_buf[m_sp];
        m_len = bswap_16(*(uint16_t*)addr);
	addr += sizeof(m_len);
        m_updates = bswap_16(*(uint16_t*)addr);
	addr += sizeof(m_updates);
	size_t required(m_sp + m_len);
	if (required > ib.m_size)
	    return -required;
	ib.m_pos = addr - ib.m_buf;
	if (ep != ib.m_pos)
	{
            cerr << "Calculated header end postion: " << ep << " is not equal to actual position: " << ib.m_pos
	        << ", starting header offset: " << m_sp << endl;
	    exit(-1);
	}
	return ep;
    }
};

struct Common : Block {
    char m_type;
    char m_symbol[6];
    void parse(InputBuffer &ib) {
	m_sp = ib.m_pos;
	char *addr = &ib.m_buf[m_sp];
        m_len = bswap_16(*(uint16_t*)addr);
        addr += sizeof(m_len);
        m_type = *addr;
        addr += sizeof(m_type);
	size_t n(sizeof(m_symbol) - 1);
	strncpy(m_symbol, addr, n);
	m_symbol[n] = '\0';
	addr += n;
	ib.m_pos = addr - ib.m_buf;
    }
};

class Printer {
    InputFile m_if;
    OutputFile m_of;
    int print(InputBuffer &ib, OutputBuffer &ob)
    {
        Header h;
	int result(h.parseAndCheck(ib));
        if (result < 0)
            return result;
        for(int i(0); i < h.m_updates; ++i)
	{
            Common c;
            c.parse(ib);
            switch(c.m_type)
	    {
                case 'T':
                    Trade t;
                    t.parse(ib);
                    result = sprintf(ob.m_buf + ob.m_size, "%d %s @ %.2f\n", 
		        t.m_ts * 100, c.m_symbol, t.m_tp / 10000.);
		    if (static_cast<int>(OutputBuffer::scm_capacity) < result || result <= 0)
		    {
                        cerr << "Failed to format trade (error: " << result
			    << ") and record it at offset: " << ob.m_size 
			    << ", parameters printed: t.m_ts = " << t.m_ts << ", c.m_symbol = "
                            << c.m_symbol << ", t.m_tp = " << t.m_tp << endl;
                        exit(-1);
		    }
		    ob.m_size += result;
                    break;
                case 'Q':
                    Quote q;
                    q.parse(ib);
                    result = sprintf(ob.m_buf + ob.m_size, "%d %s @ %.2f\n",
		        q.m_pls * 100, c.m_symbol, q.m_plp / 10000.);
		    if (static_cast<int>(OutputBuffer::scm_capacity) < result || result <= 0)
		    {
                        cerr << "Failed to format quote (error: " << result
			    << ") and record it at offset: " << ob.m_size 
			    << ", parameters printed: q.m_pls = " << q.m_pls << ", c.m_symbol = "
                            << c.m_symbol << ", q.m_plp = " << q.m_plp << endl;
                        exit(-1);
		    }
		    ob.m_size += result;
                    break;
                default:
                    cerr << "Encouneted unknown record type: " << c.m_type << endl;
                    exit(-1);
                    break;
            }
	    if (ob.m_size > OutputBuffer::scm_capacity)
	    {
                    cerr << "Required output buffer size: " << ob.m_size
                        << " is less than its actual capacity: " << OutputBuffer::scm_capacity << endl;
                    exit(-1);
	    }
            c.skipToEnd(ib);
        }
        h.skipToEnd(ib);
	return ib.m_pos;
    }
public:
    Printer(const char* ifn, const char *ofn) : m_if(ifn), m_of(ofn) { }
    ~Printer() {} 
    int print()
    {
        int iret(m_if.OpenIF());
	if (iret >= 0)
	{
            iret = m_if.SetupRead();
	}
        int oret(m_of.OpenOF());
        InputBuffer ib;
        OutputBuffer ob;
        for (size_t rcnt(0), wcnt(0); iret >= 0 && oret >= 0;)
        {
            if ((iret = m_if.Read(ib.m_buf + ib.m_size, Buffer::scm_capacity, rcnt)) > 0)
            {
		size_t bytesRead(iret);
		if ((iret = m_if.SetupRead()) < 0)
		{
		    return iret;
		}
		ib.m_size += bytesRead;
		int result(0);
		while ((result = print(ib, ob)) > 0)
		{
		    if (ob.m_size > Buffer::scm_capacity)
		    {
		        ob.m_pos = Buffer::scm_capacity;
                        if ((oret = m_of.SetupWrite(ob.m_buf, ob.m_pos)) < 0)
		        {
			    return oret;
		        }
		        ob.rewind();
		    }
	            if (oret > 0 && (oret = m_of.Write(wcnt)) > 0)
                    {
	                ++wcnt;
                    }
		}
		if (ib.m_pos == 0 && result < 0)
		{
                    cerr << "Current input buffer size is " << ib.m_size << 
		    	" bytes which is less than " << -result << " bytes required" << endl;
		    exit(-1);
		}
		if (bytesRead < Buffer::scm_capacity)
		{
		    if ((oret = m_of.SetupWrite(ob.m_buf, ob.m_size)) < 0)
                    {
                        return oret;
                    }
                    do
		    {
                        if ((oret = m_of.Write(wcnt)) > 0)
                        {
                            ++wcnt;
			}
		    }
		    while (oret >= 0 && oret != static_cast<int>(ob.m_size));
		    return oret < 0 ? oret : 0;
		}
		ib.rewind();
		++rcnt;
            }
        }
	return (iret < oret) ? iret : oret;
    }
};

int main() {
    Printer p("./input.dat", "./output.txt");
    return p.print();
}
