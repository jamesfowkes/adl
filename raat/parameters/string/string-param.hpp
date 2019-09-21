#ifndef _STRING_PARAM_H_
#define _STRING_PARAM_H_

/*
 * C/C++ Includes
 */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

class StringParam : public ParameterBase
{
public:
    StringParam(char const * const p_reset_value, uint16_t max_length, bool use_eeprom);
    void setup();
    void reset();
    uint16_t command_handler(char const * const command, char * reply);

    char const * get(void);
    void get(char * const dst);
    bool set(char const * const src);

    void save();
    void load();

    int strncmp(char const * const to_compare, int n);
    uint16_t strlen(void);

private:
    char * m_pValue;
    char * m_pResetValue;
    
    uint16_t m_length;
};

#endif