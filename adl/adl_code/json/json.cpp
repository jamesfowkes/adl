#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "device.h"
#include "adl.h"
#include "protocol.h"

/*
* Example command and reply:

{"address":00, "command":1}
{"from":0, "reply":1}

*/

typedef int (*CHAR_CONDITIONAL)(int);

static char const * skip_to_next(char const * p, CHAR_CONDITIONAL char_tester)
{
	if (!p) { return p; }
	while (!char_tester(*p)) { p++; }
	return p;
}

static char const * find_end_of_substring(char const * const haystack, char const * const subs)
{
	int subs_length = strlen(subs);
	char const * start = strstr(haystack, subs);

	return start ? start + subs_length : NULL;
}

static int json_start(char * json)
{
	return sprintf(json, "{");
}

static int json_start_level(char * json, char const * const key)
{
	int n = 0;
	if (key)
	{
		n += sprintf(json, "\"%s\":", key);
	}

	n += sprintf(json+n, "{");
	return n;
}

static int json_end_level(char * json)
{
	return sprintf(json, "}");
}

static int json_write_separator(char * json)
{
	return sprintf(json, ",");
}

static int json_write_str(char * json, char const * const key, char const * const value)
{
	return sprintf(json, "\"%s\":\"%s\"", key, value);
}

static int json_write_int(char * json, char const * const key, int value)
{
	return sprintf(json, "\"%s\":%d", key, value);
}

static uint8_t get_address(char const * const buffer)
{
	char const * addr = find_end_of_substring(buffer, "\"address\"");
	if (!addr) { return INVALID_ADDRESS; }

	addr = skip_to_next(addr, isdigit);

	return ((addr[0] - '0') * 10) + (addr[1] - '0');
}

static char const * get_command(char const * const buffer)
{
	char const * cmd = find_end_of_substring(buffer, "\"command\"");
	if (!cmd) { return NULL; }

	cmd = skip_to_next(cmd, isalnum);

	return cmd;
}

ProtocolHandler::ProtocolHandler() { this->address = INVALID_ADDRESS; }

void ProtocolHandler::process(char * json)
{
	this->address = get_address(json);
	this->command = get_command(json);
}

void ProtocolHandler::write_reply(char * buffer, char const * const reply, uint8_t reply_length)
{
	(void)reply_length;
	int i = 0;

	i += json_start(buffer+i);
	i += json_write_int(buffer+i, "from", this->address);
	i += json_write_separator(buffer+i);
	i += json_write_str(buffer+i, "reply", reply);
	i += json_end_level(buffer+i);
}
