#ifdef ARDUINO
#include <Arduino.h>
#ifdef AVR_PLATFORM
#include <avr/pgmspace.h>
#endif
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "raat-buffer.hpp"

/* RAATBuffer class */

/*
 * RAATBuffer::RAATBuffer
 *
 * Init the buffer using a buffer and length of that buffer (INCLUDING space for terminating '\0')
 */

RAATBuffer::RAATBuffer(char * buffer, uint16_t length)
{
    if (buffer)
    {
        attach(buffer, length);
    }
    else
    {
        detach();
    }
}

RAATBuffer::~RAATBuffer() {}

/*
 * RAATBuffer::writeChar
 *
 * If there is space in the buffer, add the char to the string
 * Returns true if char was written, false if not
 */

bool RAATBuffer::writeChar(char c)
{
    if (m_buffer && m_writeIndex < m_maxLength)
    {
        m_buffer[m_writeIndex++] = c;
        m_buffer[m_writeIndex] = '\0';
        return true;
    }
    return false;
}

/*
 * RAATBuffer::writeString
 *
 * Copies chars from s until s is exhausted or the buffer is full
 * Therefore, this function may only copy a partial length of s
 * Returns true if ALL of s was copied;
 */

bool RAATBuffer::writeString(const char * s)
{
    if (!s) { return false; }
    
    while(*s && (m_writeIndex < m_maxLength))
    {
        m_buffer[m_writeIndex++] = *s++;
        m_buffer[m_writeIndex] = '\0';
    }
    
    return (*s == '\0');
}

/*
 * RAATBuffer::writeLine
 *
 * As per writeString, but appends "\r\n" in addition to copying from s
 */

bool RAATBuffer::writeLine(const char * s)
{
    bool success = true;
    success &= writeString(s);
    success &= writeString("\r\n");
    return success;
}

/*
 * RAATBuffer::reset
 *
 * Makes the buffer appear to be an empty string
 */

void RAATBuffer::reset(void)
{
    m_writeIndex = 0;
    m_buffer[m_writeIndex] = '\0';
}

/*
 * RAATBuffer::c_str
 *
 * Returns pointer to the actual buffer
 */

char * RAATBuffer::c_str(void)
{
    return m_buffer;
}

/*
 * RAATBuffer::attach
 *
 * Redirects the buffer to point at a new buffer
 */

void RAATBuffer::attach(char * buffer, uint16_t length)
{
    if (buffer)
    {
        m_buffer = buffer;
        m_maxLength = length-1;
        reset();
    }
}

/*
 * RAATBuffer::full
 *
 * Returns true if the buffer is full
 */
 
bool RAATBuffer::isFull(void)
{
    return m_writeIndex == m_maxLength;
}

/*
 * RAATBuffer::detach
 *
 * Leaves the buffer floating (and therefore safe)
 */

void RAATBuffer::detach(void)
{
    m_buffer = NULL;
    m_maxLength = 0;
    m_writeIndex = 0;
}

/*
 * RAATBuffer::length
 *
 * Returns the current length of the written buffer based on write index
 */

uint16_t RAATBuffer::length(void)
{
    return m_writeIndex;
}

/*
 * RAATBuffer::remove
 *
 * Removes chars from the end of the buffer by placing a '\0' in the appropriate position
 */

void RAATBuffer::remove(uint32_t chars)
{
    if (chars > m_writeIndex)
    {
        m_writeIndex = 0;
    }
    else
    {
        m_writeIndex -= chars;
    }

    m_buffer[m_writeIndex] = '\0';
}

bool RAATBuffer::writeStringP(const char * s)
{
    bool success = false;
    if (s)
    {
        uint16_t len = strlen_P(s);
        if (m_writeIndex + len < m_maxLength)
        {
            memcpy_P(&m_buffer[m_writeIndex], s, len);
        }
        m_writeIndex += len;
        m_buffer[m_writeIndex] = '\0';
    }
    return success;
}

bool RAATBuffer::writeLineP(const char * s)
{
    bool success = true;
    success &= writeStringP(s);
    success &= writeString("\r\n");
    return success;
}

int RAATBuffer::strncmp(char * needle, int n)
{
	return ::strncmp(this->c_str(), needle, n);
}

