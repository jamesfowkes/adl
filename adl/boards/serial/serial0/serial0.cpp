/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * Arduino Includes
 */

#include <Arduino.h>

/*
 * ADL Includes
 */

#include "adl.h"

/*
 * Private Variables
 */

static adl_serial_read_char_fn * sp_adl_serial_read_char_fn;

/*
 * Public Functions
 */

void adl_serial_setup(int baudrate, adl_serial_read_char_fn& fn)
{
    Serial.begin(baudrate);
    sp_adl_serial_read_char_fn = &fn;
}

void adl_board_send(char * to_send)
{
    Serial.println(to_send);
}

void serialEvent()
{
    while (Serial.available())
    {
        (*sp_adl_serial_read_char_fn)((char)Serial.read());
    }
}
