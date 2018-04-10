#ifndef _ADL_H_
#define _ADL_H_

// ADL addresses are all positive
static const int INVALID_ADDRESS = -1;
static const int ADL_BOARD_ADDRESS = 0;

enum adl_devices
{
	ADL_DEVICE_BOARD,
{% for device in board.devices %}
	ADL_DEVICE_{{ device.cname() | upper }},
{% endfor %}
};
typedef enum adl_devices ADL_DEVICES;

static int ADL_DEVICE_COUNT = {{ board.devices | length }};

typedef int DEVICE_ADDRESS;

typedef int (*COMMAND_HANDLER)(char const * const command, char * reply);

void adl_handle_any_pending_commands();
void adl_add_char(char c);

void adl_add_char(char c);
void adl_board_send(char * to_send);

void adl_service_timer();

bool is_digit_string(char const * s);

DeviceBase& adl_get_device(DEVICE_ADDRESS address);
COMMAND_HANDLER& adl_get_command_handler(DEVICE_ADDRESS address);

class ProtocolHandlerBase
{
public:
	virtual bool process(char *) = 0;
	virtual void write_reply(char * buffer, char const * const reply, uint8_t reply_length) = 0;
	DEVICE_ADDRESS address;
	char const * command;
	
};

void adl_custom_setup(DeviceBase * pdevices[], int ndevice);
void adl_custom_loop(DeviceBase * pdevices[], int ndevice);

#endif
