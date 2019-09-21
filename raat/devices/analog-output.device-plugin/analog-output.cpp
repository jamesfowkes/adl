#include "raat.hpp"

#include "analog-output.hpp"

AnalogOutput::AnalogOutput(int pin, int limit_min, int limit_max, int reset_level)
{
    m_pin = pin;
    m_setting = 0;
    m_limit_min = limit_min;
    m_limit_max = limit_max;

    if (reset_level > m_limit_max) { reset_level = m_limit_max; }
    if (reset_level < m_limit_min) { reset_level = m_limit_min; }

    m_reset_level = reset_level;
}

void AnalogOutput::reset()
{
    this->set(m_reset_level);
}

void AnalogOutput::setup()
{
    pinMode(m_pin, OUTPUT);
    this->reset();
}

uint16_t AnalogOutput::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (is_digit_string(command))
    {
        int value = atol(command);
        if ((value >= m_limit_min) && (value <= m_limit_max))
        {
            this->set(value);
            strcpy(reply, command);
            reply_length = strlen(reply);
        }
        else
        {
            strcpy(reply, "LIM");
            reply_length = strlen(reply);
        }
    }
    else if (command[0] == '?')
    {
        sprintf(reply, "%d", m_setting);
        reply_length = strlen(reply);
    }
    else if (command[0] == 'R')
    {
        this->reset();
        sprintf(reply, "ROK");
        reply_length = strlen(reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void AnalogOutput::set(uint8_t new_value)
{
    this->m_setting = new_value;
    analogWrite(m_pin, m_setting);
}
