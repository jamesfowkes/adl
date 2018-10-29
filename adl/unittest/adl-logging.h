#ifndef _ADL_LOGGING_MOCK_H_
#define _ADL_LOGGING_MOCK_H_

class Print
{
public:
	void print(char *);
};

typedef enum adl_log_modules
{
	LOG_ADL,
	LOG_MOCK_1,
	LOG_MOCK_2,
} ADL_LOG_MODULES;

void adl_logging_setup(Print& log_printer);
void adl_log(ADL_LOG_MODULES module, char const * const fmt, ...);
void adl_logln(ADL_LOG_MODULES module, char const * const fmt, ...);

#endif
