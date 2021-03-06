#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>

#include "raat.hpp"

bool raat_convert_numeric_range(char const * const range, int32_t& min, int32_t& max, char** p_end)
{
    char * p_local_end;
    bool valid_min = false;
    bool valid_max = false;

    if (range && strlen(range) > 0)
    {
        char * p_separator = strchr((char*)range, ':');

        if (p_separator)
        {
            valid_min = raat_parse_single_numeric(range, min, &p_local_end);
            valid_max = raat_parse_single_numeric(p_separator+1, max, &p_local_end);
        }
        else
        {
            min = (int32_t)strtol(range, &p_local_end, 10);
            valid_min = p_local_end > range;
            max = min;
            valid_max = valid_min;
        }

        if (p_end && (valid_min && valid_max))
        {
            *p_end = p_local_end;
        }
    }
    else
    {
        if (p_end) { *p_end = NULL; }
    }

    return (valid_min && valid_max);
}

bool raat_parse_single_numeric(char const * const numeric, int32_t& parsed, char** p_end)
{
    if (!numeric) { return false; }

    char * p_local_end;
    int32_t local = strtol(numeric, &p_local_end, 10);

    if (p_local_end > numeric)
    {
        parsed = local;
        if (p_end)
        {
            *p_end = p_local_end;
        }
    }
    return (p_local_end > numeric);
}

bool string_is_valid_for_delimited_numerics(char const * s, char delimiter)
{
    while (*s)
    {
        if (!isdigit(*s) && (*s != delimiter))
        {
            return false;
        }
        s++;
    }
    return true;
}

char nibble_to_hex(uint8_t b)
{
    b = b & 0x0F;
    return (b < 10) ? ('0' + b) : ('A' + (b-10));
}

void byte_to_hex(char * buffer, uint8_t b)
{
    uint8_t upper = (b & 0xF0) >> 4;
    uint8_t lower = (b & 0x0F);

    buffer[0] = nibble_to_hex(upper);
    buffer[1] = nibble_to_hex(lower);
}

bool check_and_clear(bool& flag)
{
    bool value = flag;
    flag = false;
    return value;
}

/* Array Utils */
bool any_are_null(void * ptrs[], const int n)
{
    bool result = false;

    if (ptrs && n)
    {

        for (int i=0; i < n; i++)
        {
            if (!ptrs[i])
            {
                result = true;
                break;
            }
        }
    }
    return result;
}
