#include <InputFile.hpp>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
using namespace std;

InputFile::InputFile(const string &fn) : m_ifn(fn), m_ifd(-1), m_offset(0),
    m_ctx(0), m_submitted(0), m_completed(0) {}

InputFile::~InputFile()
{
    if (m_ifd >= 0)
        close(m_ifd);
    if (m_ctx != 0)
        io_destroy(m_ctx);
}

int InputFile::OpenIF()
{
    m_ifd = open(m_ifn.c_str(), O_RDONLY | O_DIRECT | O_NONBLOCK);
    if (m_ifd < 0) {
        cerr << "Can't open " << m_ifn << " input file, error: " << errno << " - " << strerror(errno) << endl;
        return -1;
    }

    int ret(io_setup(scm_queueDepth, &m_ctx));
    if (ret < 0)
    {
	int err(ret == -1 ? errno : -ret);
        cerr << "Can't allocate " << scm_queueDepth << " depth io event queue to read " <<
            m_ifn << " input file, error: " << err << " - " << strerror(err) << endl;
        return ret;
    }

    return m_ifd;
}

int InputFile::SetupRead()
{
    size_t currentQueueDepth(m_submitted - m_completed);
    if (currentQueueDepth >= scm_queueDepth)
    {
        cerr << "Can't submit read request, as number of requests in flight: " << currentQueueDepth + 1 
	    << " is more than queue depth: " << scm_queueDepth << endl;
	return 0;
    }
    size_t ind(m_submitted % scm_queueDepth);
    size_t readBufSize(m_readBuf[ind].m_size);
    if (readBufSize > 0)
    {
        cerr << "Can't submit read request #" << m_submitted + 1 << ", as read buffer #" << ind 
	    << " has not been fully consumed yet with " << readBufSize
	    << " bytes still in memory, please consider increasing queue depth beyond " << scm_queueDepth << endl;
	return 0;
    }
    iocb *pIOCB(&m_IOCB[ind]);
    io_prep_pread(pIOCB, m_ifd, m_readBuf[ind].m_buf, Buffer::scm_capacity,
        m_offset);
    m_IOCB[ind].data = &m_readBuf[ind];
    int ret(io_submit(m_ctx, scm_numEvents, &pIOCB));
    if (ret < 0)
    {
	int err(ret == -1 ? errno : -ret);
        cerr << "Failed to submit read request, io_submit returned: " << ret << ", error: "
	    << err << " - " << strerror(err) << endl;
    	return ret;
    }
    m_offset += Buffer::scm_capacity;
    return ++m_submitted;
}

int InputFile::Read(char *buf, size_t size, size_t key)
{
    size_t ind(key % scm_queueDepth);
    size_t readBufSize(m_readBuf[ind].m_size);
    if (readBufSize > 0)
    {
        memcpy(buf, m_readBuf[ind].m_buf, readBufSize);
	m_readBuf[ind].m_size = 0;
        return readBufSize;
    }
    io_event event;
    timespec timeout = {0, 0};
    int num_events(io_getevents(m_ctx, scm_numEvents, scm_numEvents, &event, &timeout));
    if (num_events < 0)
    {
	int err(num_events == -1 ? errno : -num_events);
        cerr << "Failed to get read events, io_getevents returned: " << num_events << ", error: "
	    << err << " - " << strerror(err) << endl;
    }
    else if (num_events > 0)
    {
	if (event.res < 0)
	{
            cerr << "Read failed, error: " << errno << " - " << strerror(errno) << endl;
	}
	else if (event.res > 0)
	{
	    ++m_completed;
	    if (event.res > size)
	    {
                cerr << "Can't copy " << event.res << " bytes into provided " << size << " byte read buffer" << endl;
		return -1;
	    }
	    Buffer *readBuf(static_cast<Buffer *>(event.data));
            if (readBuf == &m_readBuf[ind])
	    {
	        memcpy(buf, readBuf->m_buf, event.res);
	    }
	    else
	    {
                readBuf->m_size = event.res;
		return 0;
	    }
	}
	return event.res;
    }
    return num_events;
}
