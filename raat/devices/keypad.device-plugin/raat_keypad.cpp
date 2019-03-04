#include "raat.hpp"

#include "raat_keypad.hpp"

RAATKeypad::RAATKeypad(Keypad& keypad)
{
    m_pkeypad = &keypad;
}

void RAATKeypad::reset() {}

void RAATKeypad::setup()
{
    
}

int RAATKeypad::command_handler(char const * const command, char * reply)
{
    strcpy(reply, "CMD?");
    return 4;
}

void RAATKeypad::tick()
{
    char key = m_pkeypad->getKey();
    if (key)
    {
        Serial.println(key);
    }
}
