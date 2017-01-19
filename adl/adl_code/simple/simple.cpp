#include <stdint.h>
#include <string.h>

#include "adl.h"
#include "protocol.h"

static uint8_t get_address(char * buffer)
{
	return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

ProtocolHandler::ProtocolHandler() { this->address = INVALID_ADDRESS; }

void ProtocolHandler::process(char * buffer)
{
	this->address = get_address(buffer);
	this->command = &buffer[2];
}

void ProtocolHandler::write_reply(char * buffer, char const * const reply, uint8_t reply_length)
{
	strcpy(buffer, "reply:");
	strncpy(&buffer[6], reply, reply_length);
}
