#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstddef>

struct Buffer {
    char *m_buf;
    size_t m_size;
    static constexpr size_t scm_capacity = 8 * 4096;
    Buffer();
    ~Buffer();
    int Write(char *src, size_t srcLen);
    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer& operator=(Buffer&&) = delete;
};

#endif //BUFFER_HPP

