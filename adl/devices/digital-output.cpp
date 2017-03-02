#include <Arduino.h>

#include "device.h"
#include "adl.h"

#include "digital-output.h"

DigitalOutput::DigitalOutput(int pin)
{
	m_pin = pin;
}

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
		strcpy(reply, "OK");
		reply_length = 2;
	}
	else if (command[0] == '0')
	{
		digitalWrite(m_pin, LOW);
		strcpy(reply, "OK");
		reply_length = 2;
	}
	else
	{
		reply[0] = '?';
		reply_length = 1;
	}

	return reply_length;
}
