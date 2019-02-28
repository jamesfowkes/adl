#ifndef _RAAT_CALLBACKS_H_
#define _RAAT_CALLBACKS_H_

void raat_on_setup_start();
void raat_on_setup_complete();
void raat_on_delay_start_tick(uint8_t seconds);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params);
void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params);

#endif
