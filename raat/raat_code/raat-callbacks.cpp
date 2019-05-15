/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>

/*
 * RAT Includes
 */

#include "raat.hpp"

__attribute__((weak)) void raat_on_setup_start() {}
__attribute__((weak)) void raat_on_setup_complete() {}
__attribute__((weak)) void raat_on_delay_start_tick(uint8_t seconds) { (void)seconds; }
__attribute__((weak)) void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}
__attribute__((weak)) void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}
