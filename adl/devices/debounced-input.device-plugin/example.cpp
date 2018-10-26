#include <Arduino.h>

#include "adl-defs.h"
#include "adl-nv.h"
#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "debounced-input.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pparams; (void)ndevices; (void)nparams;
    DebouncedInput * pInput = (DebouncedInput*)pdevices[0];

    if (pInput->check_high_and_clear())
    {
        Serial.println("Input asserted high!");
    }

    if (pInput->check_low_and_clear())
    {
        Serial.println("Input asserted low!");
    }
}
