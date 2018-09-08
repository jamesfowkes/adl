#ifndef _ADL_CALLBACKS_H_
#define _ADL_CALLBACKS_H_

void adl_on_setup_start();
void adl_on_setup_complete();
void adl_on_delay_start_tick(uint8_t seconds);

void adl_custom_setup(DeviceBase * pdevices[], int ndevice, ParameterBase * pparams[], int nparams);
void adl_custom_loop(DeviceBase * pdevices[], int ndevice, ParameterBase * pparams[], int nparams);

#endif
