#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    IntegerParam * pInt = (IntegerParam*)pparams[0];

    pInt->load();

    adl_logln(LOG_APP, "Loaded integer setting %d", pInt->get());
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)nparams;
    IntegerParam * pInt = (IntegerParam*)pparams[0];

    pInt->save();
}
