#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "rgb-param.h"

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)pdevices; (void)ndevices; (void)nparams;
	RGBParam * pRGB = (RGBParam*)pparams[0];

	analogWrite(3, (uint8_t)pRGB->get(eR));
	analogWrite(5, (uint8_t)pRGB->get(eG));
	analogWrite(6, (uint8_t)pRGB->get(eB));
}