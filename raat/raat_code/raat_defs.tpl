#ifndef _RAAT_DEFS_H_
#define _RAAT_DEFS_H_

{% for define in board.defines %}
#define {{define}}
{% endfor %}

#define PROGRAM_MEMORY {{ board.progmem }}

enum raat_log_level_enum
{
	RAAT_LOG_LEVEL_NONE,
	RAAT_LOG_LEVEL_DEBUG		
};
typedef enum raat_log_level_enum RAAT_LOG_LEVEL_ENUM;

static const int RAAT_LOG_LEVEL = {{raat.raat_log_level}};

enum raat_devices_enum
{
    RAAT_DEVICE_BOARD,
{% for device in board.devices.single %}
    RAAT_DEVICE_{{ device.cname(False) | upper }},
{% endfor %}
};
typedef enum raat_devices_enum RAAT_DEVICES_ENUM;

enum raat_parameters_enum
{
{% for param in board.parameters.single %}
    RAAT_PARAM_{{ param.cname(False) | upper }},
{% endfor %}
};
typedef enum raat_parameters_enum RAAT_PARAMETERS_ENUM;

typedef {{ board.nonvolatile.address_type }} RAAT_NV_ADDR;

static const int RAAT_DEVICE_COUNT = {{ board.devices.all | length }};
static const int RAAT_PARAM_COUNT = {{ board.parameters.all | length }};

static const int RAAT_BUFFER_SIZE = {{raat.buffer_size}};

static const unsigned long RAAT_TICK_MS = {{raat.tick_duration_ms}};

#endif
