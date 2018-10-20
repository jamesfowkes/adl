#include <Arduino.h>

#include "adl-defs.h"
#include "adl-nv.h"
#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "boolean-param.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
    pinMode(13, OUTPUT);
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)nparams;
    BooleanParam * pbool = (BooleanParam*)pparams[0];

    digitalWrite(13, pbool->get() ? HIGH : LOW);
}
