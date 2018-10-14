/*
 * Arduino Includes
 */

#include <Arduino.h>

/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * ADL Includes
 */

#include "adl-oneshot-timer.h"

/*
 * Class Functions
 */

ADLOneShotTimer::ADLOneShotTimer(uint16_t period) : m_period(period), m_running(false)
{

}

void ADLOneShotTimer::start()
{
	m_running = true;
	m_start = millis();
}

bool ADLOneShotTimer::check()
{
	return m_running ? m_period <= (millis() - m_start) : false;
}

void ADLOneShotTimer::reset()
{
	m_running = false;
}

bool ADLOneShotTimer::is_running()
{
	return m_running;
}


bool ADLOneShotTimer::check_and_reset()
{
	bool expired = this->check();
	if (expired) { this->reset(); }
	return expired;
}

bool ADLOneShotTimer::check_and_restart()
{
	bool expired = this->check();
	if (expired)
	{
		this->reset();
		this->start();
	}
	return expired;
}

void ADLOneShotTimer::set_period(uint16_t period)
{
	m_period = period;
}