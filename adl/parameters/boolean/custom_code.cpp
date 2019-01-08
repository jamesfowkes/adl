#include "adl.h"

#include "boolean-param.h"

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
    pinMode(13, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)nparams;
    BooleanParam * pbool = (BooleanParam*)pparams[0];

    digitalWrite(13, pbool->get() ? HIGH : LOW);
}
