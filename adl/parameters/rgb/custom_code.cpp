#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "rgb-param.h"

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
	(void)devices; (void)pparams; (void)nparams;
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
	(void)devices; (void)nparams;
	RGBParam * pRGB = (RGBParam*)pparams[0];

	analogWrite(3, (uint8_t)pRGB->get(eR));
	analogWrite(5, (uint8_t)pRGB->get(eG));
	analogWrite(6, (uint8_t)pRGB->get(eB));
}