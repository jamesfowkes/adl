#include <Arduino.h>
#include <Keypad.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"

#include "adl_keypad.h"

ADLKeypad::ADLKeypad(Keypad& keypad)
{
    m_pkeypad = &keypad;
}

void ADLKeypad::reset() {}

void ADLKeypad::setup()
{
    
}

int ADLKeypad::command_handler(char const * const command, char * reply)
{
    strcpy(reply, "CMD?");
    return 4;
}

void ADLKeypad::tick()
{
    char key = m_pkeypad->getKey();
    if (key)
    {
        Serial.println(key);
    }
}
