#include "adl.h"

#include "adl-oneshot-timer.h"

static ADLOneShotTimer my_timer(1000);

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    my_timer.start();
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    if (my_timer.check_and_restart())
    {
        Serial.print("Timer expired and restarted at ");
        Serial.print(millis());
        Serial.println("ms!");
    }
}
