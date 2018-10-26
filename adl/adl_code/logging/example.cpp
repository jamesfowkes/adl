#include "adl.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    logln(LOG_APP, "Application");
    logln(LOG_APP_2, "Application 2");
    logln(LOG_ALT, "Application Alt.");
    logln(LOG_ANO, "Another");
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
}
