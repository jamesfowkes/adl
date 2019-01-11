#ifndef _ADL_DEFS_H_
#define _ADL_DEFS_H_

{% for define in board.defines %}
#define {{define}}
{% endfor %}

#define PROGRAM_MEMORY {{ board.progmem }}

enum adl_devices_enum
{
    ADL_DEVICE_BOARD,
{% for device in board.devices %}
    ADL_DEVICE_{{ device.cname(False) | upper }},
{% endfor %}
};
typedef enum adl_devices_enum ADL_DEVICES_ENUM;

enum adl_parameters_enum
{
{% for param in board.parameters %}
    ADL_PARAM_{{ param.cname(False) | upper }},
{% endfor %}
};
typedef enum adl_parameters_enum ADL_PARAMETERS_ENUM;

typedef {{ board.nonvolatile.address_type }} ADL_NV_ADDR;

static const int ADL_DEVICE_COUNT = {{ board.devices | length }};
static const int ADL_PARAM_COUNT = {{ board.parameters | length }};

static const int ADL_BUFFER_SIZE = {{adl.buffer_size}};

static const unsigned long ADL_TICK_MS = {{adl.tick_duration_ms}};

#endif
