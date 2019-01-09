#include "adl.h"

#include "debounced-input.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    if (devices.pButton->check_high_and_clear())
    {
        Serial.println("Input asserted high!");
    }

    if (devices.pButton->check_low_and_clear())
    {
        Serial.println("Input asserted low!");
    }
}
