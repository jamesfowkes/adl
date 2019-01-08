#include "adl.h"

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;

    adl_logln(LOG_APP, "Application");
    adl_logln(LOG_APP_2, "Application 2");
    adl_logln(LOG_ALT, "Application Alt.");
    adl_logln(LOG_ANO, "Another");
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
}
