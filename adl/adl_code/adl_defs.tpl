#ifndef _ADL_DEFS_H_
#define _ADL_DEFS_H_

enum adl_devices
{
	ADL_DEVICE_BOARD,
{% for device in board.devices %}
	ADL_DEVICE_{{ device.cname(False) | upper }},
{% endfor %}
};
typedef enum adl_devices ADL_DEVICES;

enum adl_parameters
{
{% for param in board.parameters %}
	ADL_PARAM_{{ param.cname(False) | upper }},
{% endfor %}
};
typedef enum adl_parameters ADL_PARAMETERS;

static const int ADL_DEVICE_COUNT = {{ board.devices | length }};
static const int ADL_PARAM_COUNT = {{ board.parameters | length }};

static const int ADL_BUFFER_SIZE = {{adl.buffer_size}};

#endif
