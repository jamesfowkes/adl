{% macro render_comment_header(board, context) -%}
/*
{{board.name}}
Created on {{context.time("{:%Y-%m-%d}")}}
By the Arduino Description Language tool.
 
{{board.info}}
*/

{% endmacro %}

{% macro render_declarations(board) %}

#include <stdint.h>

#include "adl.h"

{% for include in board.library_includes(False) %}
#include <{{include}}>
{% endfor %}

{% for dep in board.adl_includes(False) %}
    #include "{{dep}}"
{% endfor %}

{% for include in board.device_includes(False) %}
#include "{{include}}"
{% endfor %}

{% for include in board.parameter_includes(False) %}
#include "{{include}}"
{% endfor %}

{% for device in board.devices %}
{{device.declarations}}
{% endfor %}

static DeviceBase * s_devices[] = 
{
    {% for device in board.devices %}
    &{{device.cname()}}
    {% if not loop.last %}
    ,
    {% endif %}
    {% endfor %}
};

static const adl_devices_struct adl_devices = {
    {% for device in board.devices %}
    .p{{device.sanitised_name}} =  &{{device.cname()}}
    {% if not loop.last %}
    ,
    {% endif %}
    {% endfor %}
};

{% for parameter in board.parameters %}
{{parameter.declarations}}
{% endfor %}

static ParameterBase * s_params[] = 
{
    {% for parameter in board.parameters %}
    &{{parameter.cname()}}
    {% if not loop.last %}
    ,
    {% endif %}
    {% endfor %}
};

{% endmacro %}

{% macro render_functions(board) %}

{% for device in board.devices %}
int handle_device{{loop.index}}_command(char const * const command, char * reply)
{
    {{device.command_handler}}
}
{% endfor %}

static COMMAND_HANDLER adl_device_command_handlers[] = {
    {% for device in board.devices %}
    handle_device{{loop.index}}_command,
    {% endfor %}
};

COMMAND_HANDLER& adl_get_device_cmd_handler(DEVICE_ADDRESS address)
{
    return adl_device_command_handlers[address-1];
}

DeviceBase& adl_get_device(DEVICE_ADDRESS address)
{
    return *s_devices[address-1];
}

{% for parameter in board.parameters %}
int handle_param{{loop.index}}_command(char const * const command, char * reply)
{
    {{parameter.command_handler}}
}
{% endfor %}

static COMMAND_HANDLER adl_params[] = {
    {% for parameter in board.parameters %}
    handle_param{{loop.index}}_command,
    {% endfor %}
};

COMMAND_HANDLER& adl_get_param_cmd_handler(PARAM_ADDRESS address)
{
    return adl_params[address-1];
}

ParameterBase& adl_get_param(PARAM_ADDRESS address)
{
    return *s_params[address-1];
}

{% endmacro %}

{% macro render_setup(adl, board) -%}

void setup()
{
    adl_on_setup_start();

    adl_serial_setup({{board.serial.baudrate}}, adl_add_incoming_char);
    
    adl_nonvolatile_setup();

    adl_logging_setup({{ board.log_printer }});

    {% for device in board.devices %}
    // Setup for {{device.name}}
    {{ device.setup }}
    // END {{device.name}} setup
    {% endfor %}

    {% for param in board.parameters %}
    // Setup for {{param.name}}
    {{param.cname()}}.setup();
    // END {{param.name}} setup
    {% endfor %}

    adl_custom_setup(s_devices, ADL_DEVICE_COUNT, s_params, ADL_PARAM_COUNT);

    adl_on_setup_complete();
    
    if ({{adl.delay_start_time}})
    {
        adl_delay_start( {{adl.delay_start_time}} );
    }
}

{% endmacro %}

{% macro render_loop(board) -%}
void loop()
{
    adl_handle_any_pending_commands();
    adl_service_timer();
    adl_custom_loop(s_devices, ADL_DEVICE_COUNT, s_params, ADL_PARAM_COUNT);
}
{% endmacro %}

{% macro render_all(adl, board, context) -%}

{{ render_comment_header(board, context) }}

{{ render_declarations(board) }}

{{ render_functions(board) }}

{{ render_setup(adl, board)}}

{{ render_loop(board)}}

{% endmacro %}

{{ render_all(adl, board, context) }}
