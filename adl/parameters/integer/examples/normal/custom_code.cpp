#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
    pinMode(3, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)nparams;
    IntegerParam * pInt = (IntegerParam*)pparams[0];

    analogWrite(3, (uint8_t)pInt->get());
}
