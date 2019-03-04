#include "raat.hpp"

#include "raat-oneshot-timer.hpp"

static RAATOneShotTimer my_timer(1000);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    my_timer.start();
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    if (my_timer.check_and_restart())
    {
        Serial.print("Timer expired and restarted at ");
        Serial.print(millis());
        Serial.println("ms!");
    }
}
