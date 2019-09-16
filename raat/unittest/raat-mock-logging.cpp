/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

/*
 * Private Data
 */

/*
 * Private Functions
 */

/*
 * Public Functions
 */

void raat_logging_setup(Print& log_printer)
{
    (void)log_printer;
}

void raat_log(RAAT_LOG_MODULES module, char const * const fmt, ...)
{
    (void)module; (void)fmt;
}

void raat_logln(RAAT_LOG_MODULES module, char const * const fmt, ...)
{
    (void)module; (void)fmt;
}

void raat_log_P(RAAT_LOG_MODULES module, char const * const fmt, ...)
{
    (void)module; (void)fmt;
}

void raat_logln_P(RAAT_LOG_MODULES module, char const * const fmt, ...)
{
    (void)module; (void)fmt;
}
