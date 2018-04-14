#include <Arduino.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"

#include "debounced-input.h"

DebouncedInput::DebouncedInput(int pin, uint16_t debounce_time, bool pullup)
{
	m_pin = pin;
	m_pullup = pullup;
	m_count_max = (debounce_time + 5)/10;
	m_count = 0;
}

void DebouncedInput::reset()
{
	m_state = false;
	m_count = 0;
}

void DebouncedInput::setup()
{
	pinMode(m_pin, m_pullup ? INPUT_PULLUP : INPUT);
	this->reset();
}

bool DebouncedInput::check_high_and_clear()
{
	bool value = m_just_high;
	m_just_high = false;
	return value;
}

bool DebouncedInput::check_low_and_clear()
{
	bool value = m_just_low;
	m_just_low = false;
	return value;
}

bool DebouncedInput::state()
{
	return m_state;
}

int DebouncedInput::command_handler(char const * const command, char * reply)
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

void DebouncedInput::tick()
{

	bool high = digitalRead(m_pin) == HIGH;
	if (high)
	{
		m_count = (m_count < m_count_max) ? m_count+1 : m_count;
		
		if (!m_state && (m_count == m_count_max))
		{
			m_just_high = true;
			m_just_low = false;
		}

		if (m_count == m_count_max) { m_state = true; }
	}
	else
	{
		m_count = (m_count > 0) ? m_count-1 : m_count;
		
		if (m_state && (m_count == 0))
		{
			m_just_low = true;
			m_just_high = false;
		}

		if (m_count == 0) { m_state = false; }
	}
}
