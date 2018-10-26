#include "adl.h"

#include "digital-input.h"

DigitalInput::DigitalInput(int pin)
{
    m_pin = pin;
}

void DigitalInput::reset() {}
void DigitalInput::tick() {}

void DigitalInput::setup()
{
    pinMode(m_pin, INPUT);
}

bool DigitalInput::state()
{
    return digitalRead(m_pin) == HIGH;
}

int DigitalInput::command_handler(char const * const command, char * reply)
{
    (void)command;
    reply[0] = digitalRead(m_pin) == HIGH ? '1' : '0';
    reply[1] = '\0';
    return 1;
}
