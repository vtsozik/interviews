#include <OutputFile.hpp>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
using namespace std;

OutputFile::OutputFile(const string &fn) : m_ofn(fn), m_ofd(-1), m_offset(0),
    m_ctx(0), m_submitted(0), m_completed(0) {}

OutputFile::~OutputFile()
{
    if (m_ofd >= 0)
        close(m_ofd);
    if (m_ctx != 0)
        io_destroy(m_ctx);
}

int OutputFile::OpenOF()
{
    m_ofd = open(m_ofn.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_DIRECT | O_NONBLOCK, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (m_ofd < 0) {
        cerr << "Can't open " << m_ofn << " output file, error: " << errno << " - " << strerror(errno) << endl;
        return -1;
    }

    int ret(io_setup(scm_queueDepth, &m_ctx));
    if (ret < 0)
    {
	int err(ret == -1 ? errno : -ret);
        cerr << "Can't allocate " << scm_queueDepth << " depth io event queue to write to " <<
            m_ofn << " output file, error: " << err << " - " << strerror(err) << endl;
        return ret;
    }

    return m_ofd;
}

int OutputFile::SetupWrite(char *buf, size_t size)
{
    size_t currentQueueDepth(m_submitted - m_completed);
    if (currentQueueDepth >= scm_queueDepth)
    {
        cerr << "Can't submit write request, as number of requests in flight: " << currentQueueDepth + 1
            << " is more than queue depth: " << scm_queueDepth << endl;
        return 0;
    }
    size_t ind(m_submitted % scm_queueDepth);
    Buffer *pBuf(&m_writeBuf[ind]);
    iocb *pIOCB(&m_IOCB[ind]);
    size_t bytesWritten(pIOCB->u.c.nbytes);
    if (bytesWritten > 0)
    {
        cerr << "Can't submit write request #" << m_submitted + 1 << ", as write buffer #" << ind
            << " has " << pBuf->m_size << " bytes to be written and " << bytesWritten
            << " written bytes to be acknowledged, please consider increasing queue depth beyond " 
	    << scm_queueDepth << endl;
        return 0;
    }
    int ret(pBuf->Write(buf, size));
    if (ret > 0)
    {
        io_prep_pwrite(pIOCB, m_ofd, pBuf->m_buf, pBuf->m_size, m_offset);
        m_IOCB[ind].data = pBuf;
	int ret(io_submit(m_ctx, scm_numEvents, &pIOCB));
        if (ret < 0)
        {
            int err(ret == -1 ? errno : -ret);
            cerr << "Failed to submit read request, io_submit returned: " << ret << ", error: "
                << err << " - " << strerror(err) << endl;
            return ret;
        }
        m_offset += pBuf->m_size;
	ret = ++m_submitted;
    }
    return ret;
}

int OutputFile::Write(size_t key)
{
    size_t ind(key % scm_queueDepth);
    Buffer &buf(m_writeBuf[ind]);
    iocb *pIOCB(&m_IOCB[ind]);
    size_t bytesWritten(pIOCB->u.c.nbytes);
    if (buf.m_size != bytesWritten)
    {
        m_IOCB[ind].u.c.nbytes = 0;
	return bytesWritten;
    }
    io_event event;
    timespec timeout = {0, 0};
    int num_events(io_getevents(m_ctx, scm_numEvents, scm_numEvents, &event, &timeout));
    if (num_events < 0)
    {
        int err(num_events == -1 ? errno : -num_events);
        cerr << "Failed to get write events, io_getevents returned: " << num_events << ", error: "
            << err << " - " << strerror(err) << endl;
    }
    else if (num_events > 0)
    {
	Buffer *pBuf(static_cast<Buffer *>(event.data));
        if (pBuf->m_size != event.res)
        {
            cerr << "Incomplete write, bytes requested to be written: " 
	        << static_cast<Buffer *>(event.data)->m_size 
		<< ", bytes actually written: " << event.res
	        << ", error: " << errno << " - " << strerror(errno) << endl;
        }
        pBuf->m_size = 0;
	bytesWritten = (pBuf->m_buf == buf.m_buf) ? 0 : event.res;
	pIOCB->u.c.nbytes = bytesWritten;
        return bytesWritten;
    }
    return num_events;
}
