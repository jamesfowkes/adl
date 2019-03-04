#ifndef _RAAT_LOGGING_MOCK_H_
#define _RAAT_LOGGING_MOCK_H_

class Print
{
public:
	void print(char *);
};

typedef enum raat_log_modules
{
	LOG_RAAT,
	LOG_MOCK_1,
	LOG_MOCK_2,
} RAAT_LOG_MODULES;

void raat_logging_setup(Print& log_printer);
void raat_log(RAAT_LOG_MODULES module, char const * const fmt, ...);
void raat_logln(RAAT_LOG_MODULES module, char const * const fmt, ...);

#endif
