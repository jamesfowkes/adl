#include <stdint.h>

#include "raat.hpp"

#include "MT8870.hpp"

char press_to_char(uint8_t press)
{
    if (press == NO_PRESS)
    {
        return '-';
    }
    else if (press <= 9)
    {
        return '0' + press;
    }
    else if ((press >= 10) && (press <= 15))
    {
        return 'A' + press;
    }
    else
    {
        return '?';
    }
}

MT8870::MT8870(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t trig) :
    m_code_pins{D0, D1, D2, D3}, m_trig_pin(trig),
    m_triggered(false),
    m_presses{NO_PRESS, NO_PRESS, NO_PRESS, NO_PRESS}
{

}

void MT8870::wait_for_release()
{
    if (digitalRead(m_trig_pin) == LOW)
    {
        m_triggered = false;
    }
}

void MT8870::check_and_handle_press()
{
    if (digitalRead(m_trig_pin) == HIGH)
    {
        m_triggered = true;
        uint8_t press = 0;
        press |= (digitalRead(m_code_pins[0]) == HIGH) ? 1 : 0;
        press |= (digitalRead(m_code_pins[1]) == HIGH) ? 2 : 0;
        press |= (digitalRead(m_code_pins[2]) == HIGH) ? 4 : 0;
        press |= (digitalRead(m_code_pins[3]) == HIGH) ? 8 : 0;

        if (press == 10)
        {
            press = 0;   
        }


        this->store_press(press);
    }
}

void MT8870::tick()
{
    if (m_triggered)
    {
        this->wait_for_release();
    }
    else
    {
        this->check_and_handle_press();
    }
}

uint8_t MT8870::peek(bool asChar)
{
    return asChar ? press_to_char(m_presses[0]) : m_presses[0];
}

uint8_t MT8870::get(bool asChar)
{
    uint8_t most_recent = m_presses[0];
    m_presses[0] = m_presses[1];
    m_presses[1] = m_presses[2];
    m_presses[2] = m_presses[3];
    m_presses[3] = NO_PRESS;
    return asChar ? press_to_char(most_recent) : most_recent;
}

void MT8870::store_press(uint8_t press)
{
    m_presses[3] = m_presses[2];
    m_presses[2] = m_presses[1];
    m_presses[1] = m_presses[0];
    m_presses[0] = press;
}

void MT8870::reset()
{
    memset(m_presses, NO_PRESS, 4);
}

void MT8870::setup()
{
    pinMode(m_code_pins[0], INPUT);
    pinMode(m_code_pins[1], INPUT);
    pinMode(m_code_pins[2], INPUT);
    pinMode(m_code_pins[3], INPUT);
    pinMode(m_trig_pin, INPUT);
    this->reset();
}

uint16_t MT8870::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '?')
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            reply[i] = press_to_char(m_presses[i]);
        }
        reply[4] = '\0';
        reply_length = strlen(reply);
    }

    return reply_length;
}
