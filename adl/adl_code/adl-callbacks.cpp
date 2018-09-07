/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * ADL Includes
 */

#include "adl-callbacks.h"

__attribute__((weak)) void adl_on_setup_start() {}
__attribute__((weak)) void adl_on_setup_complete() {}
__attribute__((weak)) void adl_on_delay_start_tick(uint8_t seconds) { (void)seconds; }
