#ifndef _INTEGER_PARAM_H_
#define _INTEGER_PARAM_H_

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

#include "raat-util-limited-range-int.hpp"

template <class INT_TYPE>
class IntegerParam : public ParameterBase
{
public:
    IntegerParam(INT_TYPE reset_value, INT_TYPE min_limit, INT_TYPE max_limit,
    	bool clip_on_out_of_range, bool use_eeprom);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    
    bool set(INT_TYPE setting);
    INT_TYPE get();

    void save();
    void load();
    
private:
    INT_TYPE m_reset_value;
    LimitedRangeInt<INT_TYPE> m_value;
};


template <class INT_TYPE>
IntegerParam<INT_TYPE>::IntegerParam(INT_TYPE reset_value, INT_TYPE min_limit, INT_TYPE max_limit,
    bool clip_on_out_of_range, bool use_eeprom) :
    ParameterBase(use_eeprom, sizeof(INT_TYPE)), m_value(reset_value, min_limit, max_limit, clip_on_out_of_range)
{
    m_reset_value = reset_value;
}

template <class INT_TYPE>
void IntegerParam<INT_TYPE>::reset() {
    m_value.set(m_reset_value);
    this->on_change();
}

template <class INT_TYPE>
void IntegerParam<INT_TYPE>::setup() { ParameterBase::setup(); }

template <class INT_TYPE>
INT_TYPE IntegerParam<INT_TYPE>::get()
{
    return m_value.value();
}

template <class INT_TYPE>
bool IntegerParam<INT_TYPE>::set(INT_TYPE setting)
{
    bool success = m_value.set(setting);
    this->on_change();
    return success;
}

template <class INT_TYPE>
int IntegerParam<INT_TYPE>::command_handler(char const * const command, char * reply)
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
        sprintf(reply, "%" PRIi32, (int32_t)this->get());
        reply_length = strlen(reply);
    }

    return reply_length;
}

template <class INT_TYPE>
void IntegerParam<INT_TYPE>::save()
{
    if (m_use_eeprom)
    {
        INT_TYPE value = this->get();
        raat_nv_save(&value, m_eeprom_location);
    }
}

template <class INT_TYPE>
void IntegerParam<INT_TYPE>::load()
{
    if (m_use_eeprom)
    {
        INT_TYPE value;
        raat_nv_load(&value, m_eeprom_location);
        this->set(value);
    }
}

#endif