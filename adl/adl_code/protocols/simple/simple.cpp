#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"
#include "protocol.h"

ProtocolHandler::ProtocolHandler() { this->last_address = INVALID_ADDRESS; }

ADDRESS_TYPE ProtocolHandler::process(char * buffer)
{
	ADDRESS_TYPE address_type = adl_get_address_type_from_char(buffer[0]);

	bool valid = adl_validate_char_address(buffer+1) && (address_type != ADDRESS_TYPE_NONE);

	if (valid)
	{
		this->last_address = adl_chars_to_address(buffer+1);
		this->last_address_type = address_type;
		this->command = &buffer[3];
	}

	return address_type;
}

void ProtocolHandler::write_reply(char * buffer, char const * const reply, uint8_t reply_length)
{
	char address_tens = (this->last_address / 10);
	char address_units = this->last_address - (address_tens * 10);
	
	buffer[0] = adl_get_char_from_address_type(this->last_address_type);
	buffer[1] = address_tens + '0';
	buffer[2] = address_units + '0';
	buffer[3] = '>';
	strncpy(&buffer[4], reply, reply_length);
}
