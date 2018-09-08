#ifndef _ADL_LOGGING_H_
#define _ADL_LOGGING_H_

enum adl_log_modules
{
{% for module in board.log_modules %}
	{{ module.c_name(False) | upper }}
{% endfor %}
};

void adl_logging_setup(Print& log_printer);

void p(char const * const fmt, ...);
void pln(char const * const fmt, ...);

#endif
