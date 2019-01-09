#include "adl.h"

#include "boolean-param.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
    pinMode(13, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices;
    digitalWrite(13, params.pMy_Boolean->get() ? HIGH : LOW);
}
