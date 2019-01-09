#include "adl.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    adl_logln(LOG_APP, "Application");
    adl_logln(LOG_APP_2, "Application 2");
    adl_logln(LOG_ALT, "Application Alt.");
    adl_logln(LOG_ANO, "Another");
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
}
