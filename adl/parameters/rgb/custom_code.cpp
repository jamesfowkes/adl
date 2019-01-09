#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "rgb-param.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
	(void)devices; (void)params;
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
	(void)devices;
	analogWrite(3, (uint8_t)params.pMy_RGB_Param->get(eR));
	analogWrite(5, (uint8_t)params.pMy_RGB_Param->get(eG));
	analogWrite(6, (uint8_t)params.pMy_RGB_Param->get(eB));
}