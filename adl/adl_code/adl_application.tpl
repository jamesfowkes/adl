#ifndef _ADL_DECLS_H_
#define _ADL_DECLS_H_

{% for device in board.devices %}
    {% for include in device.includes %}
#include "{{include.name}}"
    {% endfor %}
{% endfor %}

typedef struct _adl_devices_struct
{
    {% for device in board.devices %}
    {{device.ctype}} * p{{device.sanitised_name}};
    {% endfor %}
} adl_devices_struct;

#endif
