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

typedef struct _raat_devices_struct
{
    {% for device in board.devices %}
    {{device.ctype}} * p{{device.sanitised_name}};
    {% endfor %}
} raat_devices_struct;

typedef struct _raat_params_struct
{
    {% for param in board.parameters %}
    {{param.ctype}} * p{{param.sanitised_name}};
    {% endfor %}

    {% for param_group in board.parameter_groups %}
    {{param.ctype}} * p{{param_group.sanitised_name}}[];
    {% endfor %}

} raat_params_struct;

#endif
