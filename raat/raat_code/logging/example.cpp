#include "raat.h"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    raat_logln(LOG_APP, "Application");
    raat_logln(LOG_APP_2, "Application 2");
    raat_logln(LOG_ALT, "Application Alt.");
    raat_logln(LOG_ANO, "Another");
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}
