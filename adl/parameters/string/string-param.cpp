/*
 * C/C++ Includes
 */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "string-param.h"

StringParam::StringParam(char const * const p_reset_value, uint16_t max_length, bool use_eeprom) :
    ParameterBase(use_eeprom, max_length+1),
    m_pValue(NULL),
    m_pResetValue(NULL),
    m_length(max_length)
{
    m_pValue = (char*)malloc(max_length+1);
    if (m_pValue == NULL)
    {
        m_length = 0;
    }
    if (p_reset_value)
    {
        m_pResetValue = (char*)malloc(strlen(p_reset_value)+1);
        strncpy(m_pResetValue, p_reset_value, strlen(p_reset_value)+1);
        this->reset();
    }
}

void StringParam::reset() {
    if (m_pValue && m_pResetValue)
    {
        strncpy(m_pValue, m_pResetValue, m_length);
    }
    else if (m_pValue)
    {
        m_pValue[0] = '\0';
    }
}

void StringParam::setup()
{
    this->reset();
    this->load();
}

void StringParam::get(char * const dst)
{
    if (dst && m_pValue)
    {
        strncpy(dst, m_pValue, m_length);
    }
}

bool StringParam::set(char const * const src)
{
    bool ok_to_set = false;

    ok_to_set = src && (strlen(src) <= m_length);
    if (ok_to_set)
    {
        strncpy(m_pValue, src, m_length);
        this->save();
    }

    return ok_to_set;
}

int StringParam::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'S')
    {
        if (this->set(&command[1]))
        {
            strcpy(reply, "OK");
            reply_length = strlen(reply);
        }
        else
        {
            strcpy(reply, "LEN!");
            reply_length = strlen(reply);   
        }
    }
    else if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else if (command[0] == '?' && m_pValue)
    {
        reply[0]='\'';
        this->get(&reply[1]);
        reply_length = strlen(reply);
        reply[reply_length++]='\'';
        reply[reply_length]='\0';
        
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

void StringParam::save()
{
    if (m_use_eeprom)
    {
        adl_nv_save(m_pValue, m_eeprom_location);
    }
}

void StringParam::load()
{
    if (m_use_eeprom)
    {
        adl_nv_load(m_pValue, m_eeprom_location);
    }
}
