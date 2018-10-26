#ifndef _ADL_INTERFACE_H_
#define _ADL_INTERFACE_H_

enum address_type
{
    ADDRESS_TYPE_NONE = 0,
    ADDRESS_TYPE_DEVICE = 1,
    ADDRESS_TYPE_PARAM = 2,
    ADDRESS_TYPE_MODULE = 3
};
typedef enum address_type ADDRESS_TYPE;

typedef int DEVICE_ADDRESS;
typedef int PARAM_ADDRESS;

// ADL addresses are all positive
static const int INVALID_ADDRESS = -1;
static const int ADL_BOARD_ADDRESS = 0;

typedef int (*COMMAND_HANDLER)(char const * const command, char * reply);


int adl_chars_to_address(char const * const buffer);
bool adl_validate_char_address(char const * const buffer);

ADDRESS_TYPE adl_get_address_type_from_char(char c);
ADDRESS_TYPE adl_get_address_type_from_string(char const * const s);
char adl_get_char_from_address_type(ADDRESS_TYPE t);

void adl_handle_any_pending_commands();
void adl_add_char(char c);

void adl_add_char(char c);
void adl_board_send(char * to_send);

void adl_service_timer();

bool is_digit_string(char const * s);

DeviceBase& adl_get_device(DEVICE_ADDRESS address);
ParameterBase& adl_get_param(PARAM_ADDRESS address);

COMMAND_HANDLER& adl_get_device_cmd_handler(DEVICE_ADDRESS address);
COMMAND_HANDLER& adl_get_param_cmd_handler(PARAM_ADDRESS address);

void adl_delay_start(uint8_t seconds);

int adl_board_read_progmem(char * const dst, char const * const src);

class ProtocolHandlerBase
{
public:
    virtual ADDRESS_TYPE process(char *) = 0;
    virtual void write_reply(char * buffer, char const * const reply, uint8_t reply_length) = 0;
    int last_address;
    ADDRESS_TYPE last_address_type;
    char const * command;
};

#endif
