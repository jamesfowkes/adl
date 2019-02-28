#include "raat.hpp"

#include "raat-util-limited-range-int.hpp"
#include "rgb-param.hpp"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
	(void)devices; (void)params;
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
	(void)devices;
	analogWrite(3, (uint8_t)params.pMy_RGB_Param->get(eR));
	analogWrite(5, (uint8_t)params.pMy_RGB_Param->get(eG));
	analogWrite(6, (uint8_t)params.pMy_RGB_Param->get(eB));
}