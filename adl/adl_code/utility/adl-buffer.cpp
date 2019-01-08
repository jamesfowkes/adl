#ifdef ARDUINO
#include <Arduino.h>
#ifdef AVR_PLATFORM
#include <avr/pgmspace.h>
#endif
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "adl-buffer.h"

/* ADLBuffer class */

/*
 * ADLBuffer::ADLBuffer
 *
 * Init the buffer using a buffer and length of that buffer (INCLUDING space for terminating '\0')
 */

ADLBuffer::ADLBuffer(char * buffer, uint16_t length)
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

ADLBuffer::~ADLBuffer() {}

/*
 * ADLBuffer::writeChar
 *
 * If there is space in the buffer, add the char to the string
 * Returns true if char was written, false if not
 */

bool ADLBuffer::writeChar(char c)
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
 * ADLBuffer::writeString
 *
 * Copies chars from s until s is exhausted or the buffer is full
 * Therefore, this function may only copy a partial length of s
 * Returns true if ALL of s was copied;
 */

bool ADLBuffer::writeString(const char * s)
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
 * ADLBuffer::writeLine
 *
 * As per writeString, but appends "\r\n" in addition to copying from s
 */

bool ADLBuffer::writeLine(const char * s)
{
    bool success = true;
    success &= writeString(s);
    success &= writeString("\r\n");
    return success;
}

/*
 * ADLBuffer::reset
 *
 * Makes the buffer appear to be an empty string
 */

void ADLBuffer::reset(void)
{
    m_writeIndex = 0;
    m_buffer[m_writeIndex] = '\0';
}

/*
 * ADLBuffer::c_str
 *
 * Returns pointer to the actual buffer
 */

char * ADLBuffer::c_str(void)
{
    return m_buffer;
}

/*
 * ADLBuffer::attach
 *
 * Redirects the buffer to point at a new buffer
 */

void ADLBuffer::attach(char * buffer, uint16_t length)
{
    if (buffer)
    {
        m_buffer = buffer;
        m_maxLength = length-1;
        reset();
    }
}

/*
 * ADLBuffer::full
 *
 * Returns true if the buffer is full
 */
 
bool ADLBuffer::isFull(void)
{
    return m_writeIndex == m_maxLength;
}

/*
 * ADLBuffer::detach
 *
 * Leaves the buffer floating (and therefore safe)
 */

void ADLBuffer::detach(void)
{
    m_buffer = NULL;
    m_maxLength = 0;
    m_writeIndex = 0;
}

/*
 * ADLBuffer::length
 *
 * Returns the current length of the written buffer based on write index
 */

uint16_t ADLBuffer::length(void)
{
    return m_writeIndex;
}

/*
 * ADLBuffer::remove
 *
 * Removes chars from the end of the buffer by placing a '\0' in the appropriate position
 */

void ADLBuffer::remove(uint32_t chars)
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

bool ADLBuffer::writeStringP(const char * s)
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
    }
    return success;
}

bool ADLBuffer::writeLineP(const char * s)
{
    bool success = true;
    success &= writeStringP(s);
    success &= writeString("\r\n");
    return success;
}

int ADLBuffer::strncmp(char * needle, int n)
{
	return ::strncmp(this->c_str(), needle, n);
}

