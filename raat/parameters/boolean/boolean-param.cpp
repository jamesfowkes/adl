/*
 * C/C++ Includes
 */

#include <string.h>
#include <stdint.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

#include "boolean-param.hpp"

BooleanParam::BooleanParam(bool reset_value, bool use_eeprom) : ParameterBase(use_eeprom, sizeof(bool))
{
    m_reset_value = reset_value;
    m_state = reset_value;
}

void BooleanParam::reset() {
    m_state = m_reset_value;
    this->on_change();
}

void BooleanParam::setup() { ParameterBase::setup(); }

bool BooleanParam::get()
{
    return m_state;
}

bool BooleanParam::set(bool setting)
{
    m_state = setting;
    this->on_change();
    return true;
}

int BooleanParam::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'S')
    {
        if ((command[1] == '1') || (command[1] == 'T') || (command[1] == 't') || (command[1] == 'y'))
        {
            this->set(true);
            strcpy(reply, " OK");
            reply[0] = command[1];
            reply_length = strlen(reply);
        }
        else if ((command[1] == '0') || (command[1] == 'F') || (command[1] == 'f') || (command[1] == 'n'))
        {
            this->set(false);
            strcpy(reply, " OK");
            reply[0] = command[1];
            reply_length = strlen(reply);
        }
    }
    else if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '?')
    {
        reply[0] = m_state ? '1' : '0';
        reply_length = 1;
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void BooleanParam::save()
{
    if (m_use_eeprom)
    {
        raat_nv_save(&m_state, m_eeprom_location);
    }
}

void BooleanParam::load()
{
    if (m_use_eeprom)
    {
        raat_nv_load(&m_state, m_eeprom_location);
        this->on_change();
    }
}
