#include "raat.hpp"

#include "boolean-param.hpp"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    pinMode(13, OUTPUT);
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices;
    digitalWrite(13, params.pMy_Boolean->get() ? HIGH : LOW);
}
