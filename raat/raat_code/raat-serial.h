#ifndef _RAAT_SERIAL_H_
#define _RAAT_SERIAL_H_

typedef void (raat_serial_read_char_fn)(char c);

void raat_serial_setup(long baudrate, raat_serial_read_char_fn& fn);

#endif