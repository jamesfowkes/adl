#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "raat.hpp"
#include "protocol.hpp"

/*
* Example command and reply:

/device/0/R
ROK

*/

static char const * skip_to_next(char const * p, char to_find)
{
    if (!p) { return p; }
    while (*p != to_find) { p++; }
    return p;
}

static ADDRESS_TYPE get_address(char const * const buffer, DEVICE_ADDRESS& addr)
{
    char const * paddr = buffer;
    
    if (buffer[0] != '/') { return ADDRESS_TYPE_NONE; }

    paddr++;
    paddr = skip_to_next(paddr, '/');
    paddr++;

    ADDRESS_TYPE address_type = raat_get_address_type_from_string(buffer+1);

    bool valid = (address_type != ADDRESS_TYPE_NONE) && raat_validate_char_address(paddr);

    if (valid)
    {
        addr = raat_chars_to_address(paddr);
    }
    return address_type;
}

static char const * get_command(char const * const buffer)
{
    char const * paddr = buffer+1;
    paddr = skip_to_next(paddr, '/');
    paddr++;
    paddr = skip_to_next(paddr, '/');
    paddr++;
    return paddr;
}

ProtocolHandler::ProtocolHandler() { this->last_address = INVALID_ADDRESS; }

ADDRESS_TYPE ProtocolHandler::process(char * url)
{
    this->last_address_type = get_address(url, this->last_address);

    if (this->last_address_type == ADDRESS_TYPE_NONE) { return ADDRESS_TYPE_NONE; }
    
    char const * p_cmd = get_command(url);

    strcpy(m_command_copy, p_cmd);

    this->command = m_command_copy;
    
    return this->last_address_type;
}

void ProtocolHandler::write_reply(char * buffer, char const * const reply, uint8_t reply_length)
{
    strncpy(buffer, reply, reply_length);
}
