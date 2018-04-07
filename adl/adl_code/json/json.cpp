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

static char const * skip_to_next(char const * p, char to_find)
{
	if (!p) { return p; }
	while (*p != to_find) { p++; }
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

static bool get_address(char const * const buffer, DEVICE_ADDRESS& addr)
{
	char const * paddr = find_end_of_substring(buffer, "\"address\"");
	if (!paddr) { return INVALID_ADDRESS; }

	paddr = skip_to_next(paddr, isdigit);

	bool valid = isdigit(paddr[0]) && (isdigit(paddr[1]));
	if (valid)
	{
		addr = ((paddr[0] - '0') * 10) + (paddr[1] - '0');
	}
	return valid;
}

static char const * get_command(char const * const buffer)
{
	char const * cmd = find_end_of_substring(buffer, "\"command\"");
	if (!cmd) { return NULL; }

	cmd = skip_to_next(cmd, '"');

	return cmd+1;
}

static void copy_quoted_string(char * dst, char const * src)
{
	if (*src == '"') { src++; }

	while (*src != '"')
	{
		*dst = *src;
		dst++; src++;
	}
	*dst = '\0';
}

ProtocolHandler::ProtocolHandler() { this->address = INVALID_ADDRESS; }

bool ProtocolHandler::process(char * json)
{
	if (!get_address(json, this->address)) { return false; }
	char const * p_cmd = get_command(json);

	copy_quoted_string(m_command_copy, p_cmd);

	this->command = m_command_copy;
	
	return true;
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
