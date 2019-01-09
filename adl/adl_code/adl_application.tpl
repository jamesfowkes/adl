#ifndef _ADL_DECLS_H_
#define _ADL_DECLS_H_

{% for device in board.devices %}
    {% for include in device.includes %}
#include "{{include.name}}"
    {% endfor %}
{% endfor %}

{% for param in board.parameters %}
    {% for include in param.includes %}
#include "{{include.name}}"
    {% endfor %}
{% endfor %}

typedef struct _adl_devices_struct
{
    {% for device in board.devices %}
    {{device.ctype}} * p{{device.sanitised_name}};
    {% endfor %}
} adl_devices_struct;

typedef struct _adl_params_struct
{
    {% for param in board.parameters %}
    {{param.ctype}} * p{{param.sanitised_name}};
    {% endfor %}
} adl_params_struct;

#endif
