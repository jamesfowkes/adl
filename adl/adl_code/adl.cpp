#include <Arduino.h>

#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "device.h"
#include "adl.h"
#include "protocol.h"

// ADL receives into this buffer
static char s_adl_recv_buffer[{{adl.buffer_size}}];
static uint32_t s_recv_idx = 0;

// ADL builds reply strings into this buffer
static char s_adl_tx_buffer[{{adl.buffer_size}}];

// ADL passes this buffer to application to fill with command replies 
static char s_adl_reply_buffer[16];

static bool s_command_pending = false;

static ProtocolHandler s_protocol_handler; 

static unsigned long s_timer = 0;
static const unsigned long ADL_TICK_MS = 5000;

static inline bool end_of_command(char c)
{
	return c == '\n';
}

static int adl_board_command(char const * const command, char * reply)
{
	int reply_length = 0;
	if (command[0] == 'R')
	{
		int i = 0;

		for (i = 0; i < ADL_DEVICE_COUNT; i++)
		{
			adl_get_device(i).reset();
		}
			
		strcpy(reply, "ROK");
		reply_length = strlen(reply);
	}
	else
	{
		reply[0] = '?';
		reply_length = 1;
	}
	return reply_length;
}

static int adl_process_command(uint8_t address, char const * const command, char * reply)
{
	int reply_length = 0;

	if (address == ADL_BOARD_ADDRESS)
	{
		return adl_board_command(command, reply);
	}
	else if (address > ADL_DEVICE_COUNT)
	{
		strcpy(reply, "?");
		return strlen(reply);
	}
	else
	{
		reply_length = adl_get_command_handler(address)(command, reply);
	}

	return reply_length;
}

void adl_handle_any_pending_commands()
{
	if (s_command_pending)
	{
		memset(s_adl_tx_buffer, '\0', sizeof(s_adl_tx_buffer));
		memset(s_adl_reply_buffer, '\0', sizeof(s_adl_reply_buffer));

		if (s_protocol_handler.process(s_adl_recv_buffer))
		{
			int reply_length = adl_process_command(
				s_protocol_handler.address,
				s_protocol_handler.command,
				s_adl_reply_buffer);

			s_protocol_handler.write_reply(s_adl_tx_buffer, s_adl_reply_buffer, reply_length);
		}
		else
		{
			strcpy(s_adl_tx_buffer, "ADDR?");
		}
		adl_board_send(s_adl_tx_buffer);

		s_command_pending = false;
		s_recv_idx = 0;
	}
}

void adl_service_timer()
{
	unsigned long time_now = millis();

	int i;

	if ((time_now - s_timer) > ADL_TICK_MS)
	{
		for (i = 0; i < ADL_DEVICE_COUNT; i++)
		{
			adl_get_device(i).tick();
		}
	}
}

void adl_add_char(char c)
{
	s_command_pending = end_of_command(c);
	if (!s_command_pending)
	{
		s_adl_recv_buffer[s_recv_idx++] = c;
		s_adl_recv_buffer[s_recv_idx] = '\0';
	}
}

bool is_digit_string(char const * s)
{
	if (s == NULL) { return false; }
	if (strlen(s) == 0) { return false; }

	while(*s)
	{
		if (!isdigit(*s)) { return false; }
		s++;
	}
	return true;
}
