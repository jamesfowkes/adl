{% macro render_comment_header(board, context) -%}
/*
{{board.name}}
Created on {{context.time("{:%Y-%m-%d}")}}
By the Arduino Description Language tool.
{%- from 'adl.tpl' import render_all %}
 
{{board.info}}
*/

{% endmacro %}

{% macro render_declarations(board) %}

#include <stdint.h>
#include "device.h"
#include "adl.h"

{% for include in board.includes(False) %}
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

{% endmacro %}

{% macro render_functions(board) %}

{% for device in board.devices %}
int handle_device{{loop.index}}_command(char const * const command, char * reply)
{
	{{device.command_handler}}
}
{% endfor %}

static COMMAND_HANDLER adl_commands[] = {
	{% for device in board.devices %}
	handle_device{{loop.index}}_command,
	{% endfor %}
};

int adl_device_count() { return {{board.devices | length}}; }
COMMAND_HANDLER& adl_get_command_handler(DEVICE_ADDRESS address)
{
	return adl_commands[address-1];
}

DeviceBase& adl_get_device(DEVICE_ADDRESS address)
{
	return *s_devices[address-1];
}

{% endmacro %}

{% macro render_serial_send(board) -%}
void adl_board_send(char * to_send)
{
	{{ board.serial.send("to_send") }}
}
{% endmacro %}

{% macro render_setup(board) -%}

{{ render_serial_send(board) }}

void setup()
{
	{% for device in board.devices %}
	// Setup for {{device.name}}
	{{ device.setup }}
	// END {{device.name}} setup

	{% endfor %}

	{% if board.custom_code | length %}
	adl_custom_setup(s_devices, {{board.devices | length}});
	{% endif %}

	{{ board.serial.setup }}

	{{ board.start_delay }}
}

{% endmacro %}

{% macro render_loop(board) -%}
void loop()
{
	adl_handle_any_pending_commands();
	adl_service_timer();
	{% if board.custom_code | length %}
	adl_custom_loop(s_devices, {{board.devices | length}});
	{% endif %}
}
{% endmacro %}

{% macro render_serial_event(board) -%}

{{ board.serial.read("adl_add_char") }}

{% endmacro %}

{% macro render_all(board, context) -%}

{{ render_comment_header(board, context) }}

{{ render_declarations(board) }}

{{ render_functions(board) }}

{{ render_setup(board)}}

{{ render_loop(board)}}

{{ render_serial_event(board) }}

{% endmacro %}

