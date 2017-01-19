#include <stdint.h>
#include <string.h>

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

static inline bool end_of_command(char c)
{
	return c == '\n';
}

void adl_handle_any_pending_commands()
{
	if (s_command_pending)
	{
		memset(s_adl_tx_buffer, '\0', sizeof(s_adl_tx_buffer));

		s_protocol_handler.process(s_adl_recv_buffer);

		int reply_length = adl_process_command(
			s_protocol_handler.address,
			s_protocol_handler.command,
			s_adl_reply_buffer);

		s_protocol_handler.write_reply(s_adl_tx_buffer, s_adl_reply_buffer, reply_length);

		adl_board_send(s_adl_tx_buffer);

		s_command_pending = false;
		s_recv_idx = 0;
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
