#include "adl.h"

#include "adl-oneshot-timer.h"

static ADLOneShotTimer my_timer(1000);

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;

    my_timer.start();
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;

    if (my_timer.check_and_restart())
    {
        Serial.print("Timer expired and restarted at ");
        Serial.print(millis());
        Serial.println("ms!");
    }
}
