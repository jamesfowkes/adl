#include "raat.hpp"

#include "timed-onoff.hpp"

TimedOnOff::TimedOnOff(int pin, unsigned long ontime, unsigned long offtime)
{
    m_pin = pin;
    m_ontime = ontime;
    m_offtime = offtime;
}

void TimedOnOff::reset()
{
    m_state = false;
    m_interval = m_ontime;
    m_last_time = 0;

    digitalWrite(m_pin, 0);
}

void TimedOnOff::setup()
{
    pinMode(m_pin, OUTPUT);
    this->reset();
}

uint16_t TimedOnOff::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
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

void TimedOnOff::tick()
{
    unsigned long now = millis();

    if ((now - m_last_time) > m_interval)
    {
        m_last_time = now;
        m_state = !m_state;
        m_interval = m_state ? m_offtime : m_ontime;
        digitalWrite(m_pin, m_state ? HIGH : LOW);
    }
}
