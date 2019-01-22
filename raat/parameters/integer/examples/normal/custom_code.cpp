#include "raat.h"

#include "raat-util-limited-range-int.h"
#include "integer-param.h"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    pinMode(3, OUTPUT);
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices;
    analogWrite(3, (uint8_t)params.pMy_Integer->get());
}
