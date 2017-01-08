#include <stdint.h>
#include <string.h>

#include "adl.h"

uint8_t protocol_get_device_address(char * buffer)
{
	return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

static void protocol_write_reply(char * buffer, char const * const reply, int reply_length)
{
	strcpy(buffer, "reply:");
	strncpy(&buffer[6], reply, reply_length);
}

