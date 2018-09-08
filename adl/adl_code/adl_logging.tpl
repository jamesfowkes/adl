/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdarg.h>

/* Arduino Includes */

#include "Arduino.h"

/*
 * ADL Includes
 */

#include "adl-logging.h"

/*
 * Private Data
 */

static const uint8_t LOG_BUFFER_SIZE = {{ adl.log_buffer_size }};

{% for module in board.log_modules %}
static const char {{ module.c_name(True) }}[] {{ board.progmem }} = "{{module.abbreviation}}";
{% endfor %}

static char const * const s_adl_log_module_abbreviations[] PROGMEM = {
{% for module in board.log_modules %}
	{{ module.c_name(True) }},
{% endfor %}

};

static Print * s_p_log_stream = NULL;
static char s_buf[LOG_BUFFER_SIZE];

/*
 * Public Functions
 */

void adl_logging_setup(Print& log_printer)
{
	s_p_log_stream = &log_printer;
}

void p(char const * const fmt, ...)
{   
    va_list args;
    va_start (args, fmt); vsnprintf(s_buf, LOG_BUFFER_SIZE, fmt, args); va_end (args);
    s_p_log_stream->print(s_buf);
}

void pln(char const * const fmt, ...)
{
    va_list args;
    va_start (args, fmt); vsnprintf(s_buf, LOG_BUFFER_SIZE, fmt, args); va_end (args);
    s_p_log_stream->println(s_buf);
}
