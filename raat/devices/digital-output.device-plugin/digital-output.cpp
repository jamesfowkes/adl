#include "raat.hpp"

#include "digital-output.hpp"

DigitalOutput::DigitalOutput(int pin, estartup_state startupState) :
    m_pin(pin), m_startup_state(startupState)
{
}

void DigitalOutput::tick() {}

void DigitalOutput::reset()
{
    digitalWrite(m_pin, LOW);
}

void DigitalOutput::setup()
{
    switch(m_startup_state)
    {
    case STARTUP_STATE_LOW:
        this->set(true);
        break;
    case STARTUP_STATE_HIGH:
        this->set(true);
        break;
    case STARTUP_STATE_TRISTATE:
        this->tristate();
        break;
    }
}

uint16_t DigitalOutput::command_handler(char const * const command, char * reply)
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

bool DigitalOutput::state()
{
    return digitalRead(m_pin) == HIGH;
}

void DigitalOutput::tristate()
{
    pinMode(m_pin, INPUT);
}
