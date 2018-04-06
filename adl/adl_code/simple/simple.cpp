#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "device.h"
#include "adl.h"
#include "protocol.h"

static uint8_t get_address(char * buffer)
{
	return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

static bool validate_address(char const * const buffer)
{
	if (!buffer) { return false; }

	return (isdigit(buffer[0]) && isdigit(buffer[0]));
}

ProtocolHandler::ProtocolHandler() { this->address = INVALID_ADDRESS; }

bool ProtocolHandler::process(char * buffer)
{
	bool valid = validate_address(buffer);
	if (valid)
	{
		this->address = get_address(buffer);
		this->command = &buffer[2];
	}
	return valid;
}

void ProtocolHandler::write_reply(char * buffer, char const * const reply, uint8_t reply_length)
{
	char address_tens = (this->address / 10);
	char address_units = this->address - (address_tens * 10);
	
	buffer[0] = address_tens + '0';
	buffer[1] = address_units + '0';
	buffer[2] = '>';
	strncpy(&buffer[3], reply, reply_length);
}
