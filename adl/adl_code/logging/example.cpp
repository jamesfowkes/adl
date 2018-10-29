#include "adl.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    adl_logln(LOG_APP, "Application");
    adl_logln(LOG_APP_2, "Application 2");
    adl_logln(LOG_ALT, "Application Alt.");
    adl_logln(LOG_ANO, "Another");
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
}
