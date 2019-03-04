/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

#include "raat-oneshot-timer.hpp"

/*
 * Class Functions
 */

RAATOneShotTimer::RAATOneShotTimer(uint16_t period) : m_period(period), m_running(false)
{

}

void RAATOneShotTimer::start(uint16_t period)
{
    if (period)
    {
        this->set_period(period);
    }
    m_running = true;
    m_start = millis();
}

bool RAATOneShotTimer::check()
{
    return m_running ? m_period <= (millis() - m_start) : false;
}

void RAATOneShotTimer::reset()
{
    m_running = false;
}

bool RAATOneShotTimer::is_running()
{
    return m_running;
}


bool RAATOneShotTimer::check_and_reset()
{
    bool expired = this->check();
    if (expired) { this->reset(); }
    return expired;
}

bool RAATOneShotTimer::check_and_restart()
{
    bool expired = this->check();
    if (expired)
    {
        this->reset();
        this->start();
    }
    return expired;
}

void RAATOneShotTimer::set_period(uint16_t period)
{
    m_period = period;
}