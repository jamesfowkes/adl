#include "adl.h"

#include "digital-output.h"

DigitalOutput::DigitalOutput(int pin)
{
    m_pin = pin;
}

void DigitalOutput::tick() {}

void DigitalOutput::reset()
{
    digitalWrite(m_pin, LOW);
}

void DigitalOutput::setup()
{
    pinMode(m_pin, OUTPUT);
    this->reset();
}

int DigitalOutput::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == '1')
    {
        digitalWrite(m_pin, HIGH);
        strcpy(reply, "1OK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '0')
    {
        digitalWrite(m_pin, LOW);
        strcpy(reply, "0OK");
        reply_length = strlen(reply);
    }
    else if (command[0] == 'R')
    {
        digitalWrite(m_pin, LOW);
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

void DigitalOutput::set(bool on)
{
    digitalWrite(m_pin, on ? HIGH : LOW);
    pinMode(m_pin, OUTPUT);
}

void DigitalOutput::tristate()
{
    pinMode(m_pin, INPUT);
}
