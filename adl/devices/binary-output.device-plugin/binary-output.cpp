#include "adl.h"

#include "binary-output.h"

BinaryOutput::BinaryOutput(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7)
{
    m_pins[0] = p0;
    m_pins[1] = p1;
    m_pins[2] = p2;
    m_pins[3] = p3;
    m_pins[4] = p4;
    m_pins[5] = p5;
    m_pins[6] = p6;
    m_pins[7] = p7;

    m_npins = 0;
    while (m_pins[m_npins] != PIN_NOT_USED)
    {
        m_npins++;   
    }

    m_max_value = (1 << m_npins) - 1;
}

void BinaryOutput::tick() {}

void BinaryOutput::reset()
{
    this->set(0);
}

void BinaryOutput::setup()
{
    for (uint8_t i = 0; i < m_npins; i++)
    {
        pinMode(m_pins[i], OUTPUT);
    }
    this->reset();
}

int BinaryOutput::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;

    int32_t value;
    if (adl_parse_single_numeric(command, value, NULL))
    {
        if ((value >= 0) && (value <= m_max_value))
        {
            this->set(value);
            strcpy(reply, "OK");
            reply_length = strlen(reply);
        }
        else
        {
            strcpy(reply, "VAL?");
            reply_length = strlen(reply);
        }
    }
    else if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void BinaryOutput::set(uint8_t value)
{
    if (value <= m_max_value)
    {
        for (uint8_t i = 0; i < m_npins; i++)
        {
            digitalWrite(m_pins[i], (value & (1 << i)) ? HIGH : LOW);    
            pinMode(m_pins[i], OUTPUT);
        }
    }
    
}

void BinaryOutput::tristate()
{
    for (uint8_t i = 0; i < m_npins; i++)
    {
        pinMode(m_pins[i], INPUT);
    }
}
