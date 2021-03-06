#include "raat.hpp"

#include "raat-oneshot-timer.hpp"

#include "digital-output.hpp"

DigitalOutput::DigitalOutput(uint8_t pin, estartup_state startupState) :
    m_pin(pin), m_startup_state(startupState), m_timeout(0)
{
}

void DigitalOutput::reset()
{
    digitalWrite(m_pin, LOW);
}

void DigitalOutput::setup()
{
    switch(m_startup_state)
    {
    case STARTUP_STATE_LOW:
        this->set(false);
        break;
    case STARTUP_STATE_HIGH:
        this->set(true);
        break;
    case STARTUP_STATE_TRISTATE:
        this->tristate(false);
        break;
    case STARTUP_STATE_PU:
        this->tristate(true);
        break;
    }
}

uint16_t DigitalOutput::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    uint16_t timeout = 0U;
    raat_parse_single_numeric<uint16_t>(&command[1], timeout, NULL);
    Serial.println(timeout);
    if (command[0] == '1')
    {
        this->set(true, timeout);
        strcpy(reply, "1OK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '0')
    {
        this->set(false, timeout);
        strcpy(reply, "0OK");
        reply_length = strlen(reply);
    }
    else if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else if (command[0] == 'T')
    {
        this->toggle(timeout);
        strcpy(reply, "TOK");
        reply_length = strlen(reply);

    }
    else if (command[0] == 'Z')
    {
        this->tristate(false);
        strcpy(reply, "ZOK");
        reply_length = strlen(reply);
    }
    else if (command[0] == 'P')
    {
        this->tristate(true);
        strcpy(reply, "POK");
        reply_length = strlen(reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void DigitalOutput::set(bool on, uint16_t timeout)
{
    digitalWrite(m_pin, on ? HIGH : LOW);
    pinMode(m_pin, OUTPUT);
    if (timeout)
    {
        this->start_timeout(timeout);
    }
    else
    {
        this->m_timeout.reset();
    }
}

void DigitalOutput::toggle(uint16_t timeout)
{
    this->set(!this->state(), timeout);
}

bool DigitalOutput::state()
{
    return digitalRead(m_pin) == HIGH;
}

void DigitalOutput::tristate(bool pullup)
{
    pinMode(m_pin, pullup ? INPUT_PULLUP : INPUT);
}

void DigitalOutput::start_timeout(uint16_t timeout)
{
    this->m_timeout.start(timeout);
}

void DigitalOutput::tick()
{
    if (this->m_timeout.check_and_reset())
    {
        this->toggle(0);
    }
}

uint8_t DigitalOutput::pin()
{
    return m_pin;
}
