#include "raat.hpp"

#include "random-pwm.hpp"

RandomPWM::RandomPWM(int pin, unsigned long interval, int low_limit, int high_limit)
{
    m_pin = pin;
    m_interval = interval;
    m_llimit = low_limit;
    m_hlimit = high_limit;
    m_level = 0;
    m_last_time = 0;
}

void RandomPWM::reset()
{
    m_level = 0;
    m_last_time = 0;
    analogWrite(m_pin, 0);
}

void RandomPWM::setup()
{
    randomSeed(0);
    pinMode(m_pin, OUTPUT);
    this->reset();
}

int RandomPWM::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '?')
    {
        sprintf(reply, "%d", m_level);
        reply_length = strlen(reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void RandomPWM::tick()
{
    if ((millis() - m_last_time) > m_interval)
    {
        m_last_time = millis();
        m_level = random(m_llimit, m_hlimit+1);
        analogWrite(m_pin, m_level);
    }
}
