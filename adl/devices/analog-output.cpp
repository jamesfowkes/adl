#include <Arduino.h>

#include "device.h"
#include "adl.h"

#include "analog-output.h"

AnalogOutput::AnalogOutput(int pin, int limit_min, int limit_max)
{
	m_pin = pin;
	m_setting = 0;
	m_limit_min = limit_min;
	m_limit_max = limit_max;
}

void AnalogOutput::reset()
{
	m_setting = 0;
	analogWrite(m_pin, 0);
}

void AnalogOutput::setup()
{
	pinMode(m_pin, OUTPUT);
	this->reset();
}

int AnalogOutput::command_handler(char const * const command, char * reply)
{
	int reply_length = 0;
	if (is_digit_string(command))
	{
		int value = atol(command);
		if ((value >= m_limit_min) && (value <= m_limit_max))
		{
			m_setting = value;
			analogWrite(m_pin, m_setting);
			strcpy(reply, command);
			reply_length = strlen(reply);
		}
		else
		{
			strcpy(reply, "LIM");
			reply_length = 3;
		}
	}
	else if (command[0] == '?')
	{
		sprintf(reply, "%d", m_setting);
		reply_length = strlen(reply);
	}
	else
	{
		reply[0] = '?';
		reply_length = 1;
	}

	return reply_length;
}
