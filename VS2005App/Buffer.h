#include "windows.h"

#define BLOCK 131072  // 2^17

class CBuffer
{
public:
    CBuffer();
    ~CBuffer();

    void operator+(unsigned char);
    void operator+(WORD);
    void operator+(DWORD);
    void operator+(const char*);
    char operator[](DWORD);

    DWORD getSize() { return m_buffer_pos; }
    char *getBuffer() { return m_pBuffer; }
    BOOL setAt(DWORD, DWORD);
    BOOL copy(void*, DWORD);

private:
    void resizeBuffer();

    char *m_pBuffer;             // buffer for storing data
    BOOL m_buffer_state;         // FALSE = BUFFER NOT ALLOCATED, TRUE = BUFFER ALLOCATED
    unsigned long m_block_size;  // buffer size as blocks
    unsigned long m_byte_size;   // buffer size as bytes
    unsigned long m_buffer_pos;  // current position in buffer, also effective size in bytes
};