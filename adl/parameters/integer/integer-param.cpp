/*
 * C++/Arduino Includes
 */

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS 
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

IntegerParam::IntegerParam(int32_t reset_value, int32_t min_limit, int32_t max_limit,
    bool clip_on_out_of_range, bool use_eeprom) :
    ParameterBase(use_eeprom, sizeof(int32_t)), m_value(reset_value, min_limit, max_limit, clip_on_out_of_range)
{
    m_reset_value = reset_value;
}

void IntegerParam::reset() {
    m_value.set(m_reset_value);
}

void IntegerParam::setup()
{
    this->reset();
    this->load();
}

int32_t IntegerParam::get()
{
    return m_value.value();
}

bool IntegerParam::set(int32_t setting)
{
    bool success = m_value.set(setting);
    this->save();
    return success;
}

int IntegerParam::command_handler(char const * const command, char * reply)
{
    long int value = 0;
    char * pEnd;
    int reply_length = 0;

    if (command[0] == 'S')
    {
        value = strtol(command+1, &pEnd, 10);
        if (pEnd > command)
        {
            if (this->set(value))
            {
                strcpy(reply, "OK");
                reply_length = 2;
            }
            else
            {
                strcpy(reply, "RNG!");
                reply_length = 4;
            }
        }
        else
        {
            strcpy(reply, "VAL?");
            reply_length = 4;
        }
    }
    else if (command[0] == '?')
    {
        sprintf(reply, "%" PRIi32, this->get());
        reply_length = strlen(reply);
    }

    return reply_length;
}

void IntegerParam::save()
{
    if (m_use_eeprom)
    {
        int32_t value = this->get();
        adl_nv_save(&value, m_eeprom_location);
    }
}

void IntegerParam::load()
{
    if (m_use_eeprom)
    {
        int32_t value;
        adl_nv_load(&value, m_eeprom_location);
        this->set(value);
    }
}
