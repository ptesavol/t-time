#include "stdafx.h"
#include "buffer.h"

CBuffer::CBuffer()
{
    m_buffer_pos = 0;                                                 // Initialize variables
    m_block_size = 1;
    m_byte_size = m_block_size * BLOCK;

    if(!(m_pBuffer = new char[m_byte_size])) m_buffer_state = FALSE;  // Allocate buffer
    else m_buffer_state = TRUE;
}

CBuffer::~CBuffer()
{
    if(m_pBuffer) delete [] m_pBuffer;
}

void CBuffer::operator +(unsigned char c)
{
    if(m_buffer_state) m_pBuffer[m_buffer_pos++] = c;      // Store data only if buffer allocated
    if(m_buffer_pos >= m_byte_size) resizeBuffer();        // Resize buffer if necessary
}

void CBuffer::operator +(WORD n)
{
    WORD *pn = (WORD*)(m_pBuffer + m_buffer_pos);

    if(m_buffer_state)
	{
      if((m_buffer_pos + 2) >= m_byte_size) resizeBuffer();  // Resize buffer if necessary
      if(m_buffer_state) { *pn = n; m_buffer_pos += 2; }
	}
}

void CBuffer::operator +(DWORD dw)
{
    DWORD *pdw = (DWORD*)(m_pBuffer + m_buffer_pos);

    if(m_buffer_state)
	{
      if((m_buffer_pos + 4) >= m_byte_size) resizeBuffer();  // Resize buffer if necessary
      if(m_buffer_state) { *pdw = dw; m_buffer_pos += 4; }
	}
}

void CBuffer::operator+(const char *pstr)
{
    unsigned long p, sp = strlen(pstr);

    for(p=0; p<sp; p++)
    {
      if(m_buffer_state) m_pBuffer[m_buffer_pos++] = pstr[p];   // Copy string contents
      if(m_buffer_pos >= m_byte_size) resizeBuffer();           // Resize buffer if necessary
	}
}

char CBuffer::operator[](DWORD pos)
{
    return m_pBuffer[pos];
}

void CBuffer::resizeBuffer()
{
    char *tmp;
    unsigned long block_size;

    if(!m_buffer_state) return;                            // No buffer, return

    block_size = m_block_size + 1;                         // New buffer size

    // Allocate new buffer and copy old data
    if(!(tmp = new char[block_size * BLOCK]))              // Allocation failed
	{
      delete [] m_pBuffer; m_pBuffer = NULL;               // Free old buffer, no buffer
      m_buffer_state = FALSE;
	}
	else                                                   // Allocation succeeded
	{
      CopyMemory(tmp, m_pBuffer, m_byte_size);             // Copy old buffer and set new sizes
      m_block_size = block_size;
      m_byte_size = m_block_size * BLOCK;

      delete [] m_pBuffer; m_pBuffer = tmp;                // Free old buffer, set pointer to new
      m_buffer_state = TRUE;
	}
}

BOOL CBuffer::setAt(DWORD pos, DWORD dw)
{
    BOOL ret = TRUE;
    DWORD *pdw = (DWORD*)(m_pBuffer + pos);

    if((pos + 4) < m_byte_size) *pdw = dw;
    else ret = FALSE;

    return ret;
}

BOOL CBuffer::copy(void *ptr, DWORD size)
{
    char *pc = (char*)ptr;

    for(DWORD i=0; i<size; i++)
	{
      if(m_buffer_state) m_pBuffer[m_buffer_pos++] = pc[i];  // Store data only if buffer allocated
      if(m_buffer_pos >= m_byte_size) resizeBuffer();        // Resize buffer if necessary	
	}

    return TRUE;
}