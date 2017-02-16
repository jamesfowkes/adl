#include <Arduino.h>

#include "device.h"
#include "adl.h"

#include "digital-input.h"

DigitalInput::DigitalInput(int pin)
{
	m_pin = pin;
}

void DigitalInput::reset() {}

void DigitalInput::setup()
{
	pinMode(m_pin, INPUT);
}

int DigitalInput::command_handler(char const * const command, char * reply)
{
	reply[0] = digitalRead(m_pin) == HIGH ? '1' : '0';
	reply[1] = '\0';
	return 1;
}
