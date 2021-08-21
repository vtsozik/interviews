#include <Buffer.hpp>

#include <string.h>

#include <iostream>
using namespace std;

Buffer::Buffer() : m_buf(new char[scm_capacity]), m_size(0)
{
    if (m_buf == NULL)
    {
        cerr << "Failed to allocate char buffer of size: " << scm_capacity << endl;
        exit(-1);
    }
}

Buffer::~Buffer()
{
    if (m_buf != NULL)
    {
        delete[] m_buf;
    }
}

int Buffer::Write(char *src, size_t srcLen)
{
    if (scm_capacity < srcLen || srcLen < 1)
    {
        cerr << "Buffer capacity: " << scm_capacity << " is less than " << srcLen 
	    << " bytes to be written" << endl;
        return -1;
    }
    m_size = srcLen;
    memcpy(m_buf, src, m_size);
    return m_size;
}
