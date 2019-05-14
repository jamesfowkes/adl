/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* Arduino Includes */

#include "Arduino.h"

/*
 * RAAT Includes
 */

#include "raat.hpp"

static const char INVALID_RANGE_MSG[] {{ board.progmem }} = "Invalid range";
static const char INVALID_VALUES_MSG[] {{ board.progmem }} = "Invalid values";
static const char VALUE_COUNT_INCORRECT_MSG[] {{ board.progmem }} = "Value count incorrect (%u) '%s'";

int raat_msg_invalid_range(char * reply)
{
    return raat_board_strcpy_progmem(reply, INVALID_RANGE_MSG);
}

int raat_msg_invalid_values(char * reply)
{
    return raat_board_strcpy_progmem(reply, INVALID_VALUES_MSG);
}

int raat_msg_wrong_number_of_values(char * reply, uint8_t parsed_count, char const * const s)
{
    return raat_board_sprintf_progmem(reply, VALUE_COUNT_INCORRECT_MSG, parsed_count, s);
}
