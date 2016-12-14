#ifndef _ADL_H_
#define _ADL_H_

typedef int (*COMMAND_HANDLER)(char const * const command, char * reply);

void adl_handle_any_pending_commands();
void adl_add_char(char c);
int adl_process_command(uint8_t address, char const * const command, char * reply);
void adl_add_char(char c);
void adl_board_send(char * to_send);

#endif
