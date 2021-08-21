#ifndef OUTPUT_FILE_HPP
#define OUTPUT_FILE_HPP
#include <libaio.h>
#include <Buffer.hpp>

#include <string>
using namespace std;

class OutputFile {
    static constexpr long scm_numEvents = 1;
    static constexpr size_t scm_queueDepth = 128;
    const string m_ofn;
    int m_ofd;
    size_t m_offset;
    io_context_t m_ctx;
    iocb m_IOCB[scm_queueDepth];
    Buffer m_writeBuf[scm_queueDepth];
    size_t m_submitted;
    size_t m_completed;

public:
    OutputFile(const string &fn);

    ~OutputFile();

    int OpenOF();

    int SetupWrite(char *buf, size_t size);

    int Write(size_t key);
};

#endif //OUTPUT_FILE_HPP
