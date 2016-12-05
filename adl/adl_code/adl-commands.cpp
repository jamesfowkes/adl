#include "adl-commands.h"

static char s_adl_buffer[{{adl_buffer_size}}];
static bool s_command_pending = false;
static uint32_t s_write_idx = 0;

static inline bool end_of_command(char c)
{
	return c == "\n"
}

void handle_any_pending_commands()
{
	if (s_command_pending)
	{
		process_command(s_adl_buffer);
		s_command_pending = false
	}
}

void adl_add_char(char c)
{
	s_write_buffer[s_write_idx++] = c;
	s_command_pending = end_of_command(c);
}
