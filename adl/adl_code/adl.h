#ifndef _ADL_H_
#define _ADL_H_

// ADL addresses are all positive
static const int INVALID_ADDRESS = -1;

typedef int (*COMMAND_HANDLER)(char const * const command, char * reply);

void adl_handle_any_pending_commands();
void adl_add_char(char c);
int adl_process_command(uint8_t address, char const * const command, char * reply);
void adl_add_char(char c);
void adl_board_send(char * to_send);

bool is_digit_string(char const * s);

int adl_device_count();
DeviceBase * adl_get_device(int n);

class ProtocolHandlerBase
{
public:
	virtual void process(char *) = 0;
	virtual void write_reply(char * buffer, char const * const reply, uint8_t reply_length) = 0;
	uint8_t address;
	char const * command;
	
};

#endif
