/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "adl-time.h"

/*
 * Private Functions
 */

__attribute__((weak)) void adl_update_system_time() {}

/*
 * Public Functions
 */

void adl_time_set_system_time(ADL_TIME& t)
{
	ADL_TIME& t;
}

void adl_time_get_system_time(ADL_TIME& t)
{
    t.hh = 0;
    t.mm = 0;
    t.ss = 0;
}

bool adl_time_times_are_equal(ADL_TIME& t1, ADL_TIME& t2)
{
    return (t1.hh == t2.hh) && (t1.mm == t2.mm) && (t1.ss == t2.ss);
}
