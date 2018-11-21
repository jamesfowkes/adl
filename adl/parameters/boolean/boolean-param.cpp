/*
 * C/C++ Includes
 */

#include <string.h>
#include <stdint.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "boolean-param.h"

BooleanParam::BooleanParam(bool reset_value, bool use_eeprom) : ParameterBase(use_eeprom, sizeof(bool))
{
    m_reset_value = reset_value;
    m_state = reset_value;
}

void BooleanParam::reset() {
    m_state = m_reset_value;
}

void BooleanParam::setup()
{
    this->reset();
}

bool BooleanParam::get()
{
    return m_state;
}

bool BooleanParam::set(bool setting)
{
    m_state = setting;
    return true;
}

int BooleanParam::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'S')
    {
        if ((command[1] == '1') || (command[1] == 'T') || (command[1] == 't') || (command[1] == 'y'))
        {
            m_state = true;
            strcpy(reply, " OK");
            reply[0] = command[1];
            reply_length = strlen(reply);
        }
        else if ((command[1] == '0') || (command[1] == 'F') || (command[1] == 'f') || (command[1] == 'n'))
        {
            m_state = false;
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
        adl_nv_save(&m_state, m_eeprom_location);
    }
}

void BooleanParam::load()
{
    if (m_use_eeprom)
    {
        adl_nv_load(&m_state, m_eeprom_location);
    }
}
