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

#include "raat.h"

{% for include in board.library_includes(False) %}
#include <{{include}}>
{% endfor %}

{% for dep in board.raat_includes(False) %}
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

static DeviceBase * s_device_pointers[] = 
{
    {% for device in board.devices %}
    &{{device.cname()}}
    {% if not loop.last %}
    ,
    {% endif %}
    {% endfor %}
};

static const raat_devices_struct raat_devices = {
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

static ParameterBase * s_params_pointers[] = 
{
    {% for parameter in board.parameters %}
    &{{parameter.cname()}}
    {% if not loop.last %}
    ,
    {% endif %}
    {% endfor %}
};

static const raat_params_struct raat_params = {
    {% for param in board.parameters %}
    .p{{param.sanitised_name}} =  &{{param.cname()}}
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

static COMMAND_HANDLER raat_device_command_handlers[] = {
    {% for device in board.devices %}
    handle_device{{loop.index}}_command,
    {% endfor %}
};

COMMAND_HANDLER& raat_get_device_cmd_handler(DEVICE_ADDRESS address)
{
    return raat_device_command_handlers[address-1];
}

DeviceBase& raat_get_device(DEVICE_ADDRESS address)
{
    return *s_device_pointers[address-1];
}

{% for parameter in board.parameters %}
int handle_param{{loop.index}}_command(char const * const command, char * reply)
{
    {{parameter.command_handler}}
}
{% endfor %}

static COMMAND_HANDLER raat_param_command_handlers[] = {
    {% for parameter in board.parameters %}
    handle_param{{loop.index}}_command,
    {% endfor %}
};

COMMAND_HANDLER& raat_get_param_cmd_handler(PARAM_ADDRESS address)
{
    return raat_param_command_handlers[address-1];
}

ParameterBase& raat_get_param(PARAM_ADDRESS address)
{
    return *s_params_pointers[address-1];
}

{% endmacro %}

{% macro render_setup(raat, board) -%}

void setup()
{
    raat_on_setup_start();

    raat_serial_setup({{board.serial.baudrate}}, raat_add_incoming_char);
    
    raat_nonvolatile_setup();

    raat_logging_setup({{ board.log_printer }});

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

    raat_custom_setup(raat_devices, raat_params);

    raat_on_setup_complete();
    
    if ({{raat.delay_start_time}})
    {
        raat_delay_start( {{raat.delay_start_time}} );
    }
}

{% endmacro %}

{% macro render_loop(board) -%}
void loop()
{
    raat_handle_any_pending_commands();
    raat_service_timer();
    raat_custom_loop(raat_devices, raat_params);
}
{% endmacro %}

{% macro render_all(raat, board, context) -%}

{{ render_comment_header(board, context) }}

{{ render_declarations(board) }}

{{ render_functions(board) }}

{{ render_setup(raat, board)}}

{{ render_loop(board)}}

{% endmacro %}

{{ render_all(raat, board, context) }}