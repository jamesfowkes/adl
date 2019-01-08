#ifndef _ADL_CALLBACKS_H_
#define _ADL_CALLBACKS_H_

void adl_on_setup_start();
void adl_on_setup_complete();
void adl_on_delay_start_tick(uint8_t seconds);

void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams);
void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams);

#endif
