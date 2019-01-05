#ifndef _ADL_SERIAL_H_
#define _ADL_SERIAL_H_

typedef void (adl_serial_read_char_fn)(char c);

void adl_serial_setup(long baudrate, adl_serial_read_char_fn& fn);

#endif