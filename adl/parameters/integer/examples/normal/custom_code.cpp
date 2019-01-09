#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
    pinMode(3, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices;
    analogWrite(3, (uint8_t)params.pMy_Integer->get());
}
