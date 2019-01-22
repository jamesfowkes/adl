/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * RAAT Includes
 */

#include "raat.h"

#include "raat-time.h"

/*
 * Private Functions
 */

__attribute__((weak)) void raat_update_system_time() {}

/*
 * Public Functions
 */

void raat_time_set_system_time(RAAT_TIME& t)
{
	RAAT_TIME& t;
}

void raat_time_get_system_time(RAAT_TIME& t)
{
    t.hh = 0;
    t.mm = 0;
    t.ss = 0;
}

bool raat_time_times_are_equal(RAAT_TIME& t1, RAAT_TIME& t2)
{
    return (t1.hh == t2.hh) && (t1.mm == t2.mm) && (t1.ss == t2.ss);
}
