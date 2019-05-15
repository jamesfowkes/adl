#include "raat.hpp"

#include "debounced-input.hpp"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
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
