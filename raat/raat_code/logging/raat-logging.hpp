#ifndef _RAAT_LOGGING_H_
#define _RAAT_LOGGING_H_

typedef enum raat_log_modules
{
	LOG_RAAT,
{% for module in board.log_modules %}
    LOG_{{ module.prefix }},
{% endfor %}
} RAAT_LOG_MODULES;

void raat_logging_setup(Print& log_printer);

void raat_log(RAAT_LOG_MODULES module, char const * const fmt, ...);
void raat_logln(RAAT_LOG_MODULES module, char const * const fmt, ...);

void raat_log_P(RAAT_LOG_MODULES module, char const * const fmt, ...);
void raat_logln_P(RAAT_LOG_MODULES module, char const * const fmt, ...);

#endif
