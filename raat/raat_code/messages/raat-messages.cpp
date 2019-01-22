/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*
 * RAAT Includes
 */

#include "raat-messages.h"

int raat_msg_invalid_range(char * reply)
{
    strcpy(reply, "Invalid range");
    return strlen(reply);
}

int raat_msg_invalid_values(char * reply)
{
    strcpy(reply, "Invalid values");
    return strlen(reply);
}

int raat_msg_wrong_number_of_values(char * reply, uint8_t parsed_count, char const * const s)
{
    return sprintf(reply, "Value count incorrect (%u) '%s'", parsed_count, s);
}
