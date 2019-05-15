/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * Arduino Includes
 */

#include <Arduino.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

/*
 * Private Variables
 */

static raat_serial_read_char_fn * sp_raat_serial_read_char_fn;

/*
 * Public Functions
 */

void raat_serial_setup(long baudrate, raat_serial_read_char_fn& fn)
{
    Serial.begin(baudrate);
    sp_raat_serial_read_char_fn = &fn;
}

void raat_board_send(char * to_send)
{
    Serial.println(to_send);
}

void serialEvent()
{
    while (Serial.available())
    {

        (*sp_raat_serial_read_char_fn)((char)Serial.read());
    }
}
