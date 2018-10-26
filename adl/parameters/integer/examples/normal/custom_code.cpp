#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
    pinMode(3, OUTPUT);
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)nparams;
    IntegerParam * pInt = (IntegerParam*)pparams[0];

    analogWrite(3, (uint8_t)pInt->get());
}
