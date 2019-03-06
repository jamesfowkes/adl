#ifndef _RAAT_DECLS_H_
#define _RAAT_DECLS_H_

{% for include in board.library_includes(False) %}
#include "{{include}}"
{% endfor %}

{% for include in board.device_includes(False) %}
#include "{{include}}"
{% endfor %}

{% for include in board.parameter_includes(False) %}
#include "{{include}}"
{% endfor %}

struct _raat_devices_struct
{
    {% for device in board.devices.all -%}
    {{device.ctype}} * p{{device.sanitised_name}};
    {% endfor %}
    {% for device_group in board.devices.grouped -%}
    {{device_group.base_device.ctype}} * p{{device_group.base_device.sanitised_name}}[{{device_group.count}}];
    {% endfor %}
};
typedef struct _raat_devices_struct raat_devices_struct;

struct _raat_params_struct
{
    {% for param in board.parameters.all -%}
    {{param.ctype}} * p{{param.sanitised_name}};
    {% endfor %}
    {% for param_group in board.parameters.grouped -%}
    {{param_group.base_param.ctype}} * p{{param_group.base_param.sanitised_name}}[{{param_group.count}}];
    {% endfor %}
};
typedef struct _raat_params_struct raat_params_struct;

#endif
