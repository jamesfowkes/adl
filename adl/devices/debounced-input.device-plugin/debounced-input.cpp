#include "adl.h"

#include "adl-util-debouncer.h"
#include "debounced-input.h"

DebouncedInput::DebouncedInput(int pin, uint16_t debounce_time, bool pullup) :
    m_pin(pin),
    m_pullup(pullup),
    m_debouncer(*this, debounce_time)
{
}

void DebouncedInput::reset()
{
    m_debouncer.reset();
}

void DebouncedInput::setup()
{
    pinMode(m_pin, m_pullup ? INPUT_PULLUP : INPUT);
    this->reset();
}

bool DebouncedInput::check_high_and_clear()
{
    return m_debouncer.check_high_and_clear();
}

bool DebouncedInput::check_low_and_clear()
{
    return m_debouncer.check_low_and_clear();
}

bool DebouncedInput::state()
{
    return m_debouncer.state();
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
    this->m_debouncer.tick();
}

bool DebouncedInput::read()
{
    return digitalRead(m_pin) == LOW;
}
