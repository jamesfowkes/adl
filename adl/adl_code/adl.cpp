#include <stdint.h>
#include <string.h>

#include "adl.h"

// ADL receives into this buffer
static char s_adl_recv_buffer[{{adl.buffer_size}}];
static uint32_t s_recv_idx = 0;

// ADL builds reply strings into this buffer
static char s_adl_tx_buffer[{{adl.buffer_size}}];
static uint32_t s_tx_write_idx = 0;

// ADL passes this buffer to application to fill with command replies 
static char s_adl_reply_buffer[16];

static bool s_command_pending = false;

static inline bool end_of_command(char c)
{
	return c == '\n';
}

static uint8_t get_device_address(char * buffer)
{
	return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

static void adl_write_reply(char * buffer, char const * const reply, int reply_length)
{
	strcpy(buffer, "reply:");
	strncpy(&buffer[6], reply, reply_length);
}

void adl_handle_any_pending_commands()
{
	if (s_command_pending)
	{
		uint8_t address = get_device_address(s_adl_recv_buffer);
		char * command_start = &s_adl_recv_buffer[2];
		int reply_length = adl_process_command(address, command_start, s_adl_reply_buffer);

		adl_write_reply(s_adl_tx_buffer, s_adl_reply_buffer, reply_length);

		adl_board_send(s_adl_tx_buffer);

		s_command_pending = false;
		s_recv_idx = 0;
	}
}

void adl_add_char(char c)
{
	s_adl_recv_buffer[s_recv_idx++] = c;
	s_command_pending = end_of_command(c);
}
