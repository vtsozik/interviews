#ifndef INPUT_FILE_HPP
#define INPUT_FILE_HPP
#include <Buffer.hpp>
#include <libaio.h>

#include <string>
using namespace std;

class InputFile {
    static constexpr long scm_numEvents = 1;
    static constexpr size_t scm_queueDepth = 128;
    const string m_ifn;
    int m_ifd;
    size_t m_offset;
    io_context_t m_ctx;
    iocb m_IOCB[scm_queueDepth];
    Buffer m_readBuf[scm_queueDepth];
    size_t m_submitted;
    size_t m_completed;

public:
    InputFile(const string &fn);

    ~InputFile();

    int OpenIF();

    int SetupRead();

    int Read(char *buf, size_t size, size_t key);

};

#endif //INPUT_FILE_HPP
