#include <stdint.h>
#include <stdlib.h>
#include "adl.h"
#include "adl-util-delimited-stream-parser.h"

DelimitedStreamParser::DelimitedStreamParser(char start, char end, adl_string_buffer& buffer, PARSER_CALLBACK on_parsed_cb):
m_start(start), m_end(end), m_pbuffer(&buffer), m_on_parsed_cb(on_parsed_cb), m_write_index(0)
{
    if (m_end != '\0')
    {
        this->set_state((m_start == '\0') ? PARSER_STATE_PARSING : PARSER_STATE_WAITING);
        this->reset();
    }
    else
    {
        this->set_state(PARSER_STATE_ERROR);
    }
}

void DelimitedStreamParser::set_state(PARSER_STATE new_state)
{
    m_state = new_state;
}

void DelimitedStreamParser::reset()
{
    m_write_index = 0;
    m_pbuffer->buffer[m_write_index] = '\0';
}

bool DelimitedStreamParser::add_to_buffer(char c)
{
    bool can_write = (m_write_index < m_pbuffer->max_size);
    if (can_write)
    {
        m_pbuffer->buffer[m_write_index++] = c;
        m_pbuffer->buffer[m_write_index] = '\0';
    }
    return can_write;
}

void DelimitedStreamParser::run(char c)
{
    switch(m_state)
    {
    case PARSER_STATE_WAITING:
    case PARSER_STATE_OVERFLOW:
        if (c == m_start)
        {
            this->set_state(PARSER_STATE_PARSING);
        }
        break;
    case PARSER_STATE_PARSING:
        if (c == m_end)
        {
            m_on_parsed_cb(m_pbuffer->buffer);
            this->set_state((m_start == '\0') ? PARSER_STATE_PARSING : PARSER_STATE_WAITING);
            this->reset();
        }
        else
        {
            if (!add_to_buffer(c))
            {
                this->set_state(PARSER_STATE_OVERFLOW);
            }
        }
        break;
    case PARSER_STATE_ERROR:
        break;
    }
}

PARSER_STATE DelimitedStreamParser::state() { return m_state; }
