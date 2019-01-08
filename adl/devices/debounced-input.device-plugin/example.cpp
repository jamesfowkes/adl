#include "adl.h"

#include "debounced-input.h"

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;

    if (devices.pDebounced_Input->check_high_and_clear())
    {
        Serial.println("Input asserted high!");
    }

    if (devices.pDebounced_Input->check_low_and_clear())
    {
        Serial.println("Input asserted low!");
    }
}
