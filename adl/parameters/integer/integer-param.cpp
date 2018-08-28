/*
 * C++/Arduino Includes
 */

#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * ADL Includes
 */

#include "adl-util-limited-range-int.h"
#include "parameter.h"
#include "integer-param.h"

IntegerParam::IntegerParam(int32_t reset_value, int32_t min_limit, int32_t max_limit, bool clip_on_out_of_range) :
m_value(reset_value, min_limit, max_limit, clip_on_out_of_range)
{
	m_reset_value = reset_value;
}

void IntegerParam::reset() {
	m_value.set(m_reset_value);
}

void IntegerParam::setup()
{
	this->reset();
}

int32_t IntegerParam::get()
{
	return m_value.value();
}

bool IntegerParam::set(int32_t setting)
{
	return m_value.set(setting);
}

int IntegerParam::command_handler(char const * const command, char * reply)
{
	long int value = 0;
	char * pEnd;
	int reply_length;

	if (command[0] == 'S')
	{
		value = strtol(command, &pEnd, 10);
		if (pEnd > command)
		{
			if ((value <= INT32_MAX) && (value >= INT32_MIN))
			{
				strcpy(reply, "OK");
				reply_length = 2;
			}
		}
	}
	else if (command[0] == '?')
	{
		sprintf(reply, "%d", this->get());
	}

	return reply_length;
}
