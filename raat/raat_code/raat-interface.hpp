#ifndef _RAAT_INTERFACE_H_
#define _RAAT_INTERFACE_H_

enum address_type
{
    ADDRESS_TYPE_NONE = 0,
    ADDRESS_TYPE_DEVICE = 1,
    ADDRESS_TYPE_PARAM = 2,
    ADDRESS_TYPE_MODULE = 3
};
typedef enum address_type ADDRESS_TYPE;

typedef int16_t RAAT_ADDRESS;
typedef RAAT_ADDRESS DEVICE_ADDRESS;
typedef RAAT_ADDRESS PARAM_ADDRESS;

// RAAT addresses are all positive
static const DEVICE_ADDRESS INVALID_ADDRESS = -1;
static const DEVICE_ADDRESS RAAT_BOARD_ADDRESS = 0;

typedef uint16_t (*COMMAND_HANDLER)(char const * const command, char * reply);

RAAT_ADDRESS raat_chars_to_address(char const * const buffer);
bool raat_validate_char_address(char const * const buffer);

ADDRESS_TYPE raat_get_address_type_from_char(char c);
ADDRESS_TYPE raat_get_address_type_from_string(char const * const s);
char raat_get_char_from_address_type(ADDRESS_TYPE t);

void raat_handle_any_pending_commands();

void raat_add_incoming_char(char c);
void raat_add_incoming_command(char const * cmd);

void raat_board_send(char * to_send);

void raat_service_timer();

bool is_digit_string(char const * s);

DeviceBase& raat_get_device(DEVICE_ADDRESS address);
ParameterBase& raat_get_param(PARAM_ADDRESS address);

COMMAND_HANDLER& raat_get_device_cmd_handler(DEVICE_ADDRESS address);
COMMAND_HANDLER& raat_get_param_cmd_handler(PARAM_ADDRESS address);

void raat_delay_start(uint8_t seconds);

int raat_board_strcpy_progmem(char * const pMemory, char const * const pProgmem);
int raat_board_memcmp_progmem(char * const pMemory, char const * const pProgmem, size_t len);
int raat_board_strcmp_progmem(char * const pMemory, char const * const pProgmem);
int raat_board_strncmp_progmem(char const * const pMemory, char const * const pProgmem, size_t len);
int raat_board_strlen_progmem(char const * const pProgmem);
void raat_board_memcpy_progmem(char * pMemory, char const * const pProgmem, size_t len);

uint16_t raat_board_max_adc_reading();

class ProtocolHandlerBase
{
public:
    virtual ADDRESS_TYPE process(char *) = 0;
    virtual void write_reply(char * buffer, char const * const reply, uint8_t reply_length) = 0;
    RAAT_ADDRESS last_address;
    ADDRESS_TYPE last_address_type;
    char const * command;
};

#endif
