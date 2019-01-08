/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>

/*
 * ADL Includes
 */

#include "adl.h"

__attribute__((weak)) void adl_on_setup_start() {}
__attribute__((weak)) void adl_on_setup_complete() {}
__attribute__((weak)) void adl_on_delay_start_tick(uint8_t seconds) { (void)seconds; }
__attribute__((weak)) void adl_custom_setup(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
}
__attribute__((weak)) void adl_custom_loop(const adl_devices_struct& devices, ParameterBase * pparams[], int nparams)
{
    (void)devices; (void)pparams; (void)nparams;
}
