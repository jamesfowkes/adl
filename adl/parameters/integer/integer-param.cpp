/*
 * C++/Arduino Includes
 */

#include "stdint.h"
#include "string.h"

/*
 * ADL Includes
 */

#include "parameter.h"
#include "integer-param.h"
#include "adl-util-limited-range-int.h"

IntegerParam::IntegerParam(int32_t reset_value, int32_t min_limit, int32_t max_limit)
{
	m_min = min_limit;
	m_max = max_limit;
	m_reset_value = reset_value;
	m_state = reset_value;
}

void IntegerParam::reset() {
	m_state = m_reset_value;
}

void IntegerParam::setup()
{
	this->reset();
}

int32_t IntegerParam::get()
{
	return m_state;
}

bool IntegerParam::set(int32_t setting)
{
	bool valid = (setting <= m_max) && (setting >= m_min);

	if (valid)
	{
		m_state = setting;
	}

	return valid;
}

int IntegerParam::command_handler(char const * const command, char * reply)
{
	int reply_length = 0;
	if ((command[0] == '1') || (command[0] == 'T') || (command[0] == 't') || (command[0] == 'y'))
	{
		m_state = true;
		strcpy(reply, " OK");
		reply[0] = command[0];
		reply_length = strlen(reply);
	}
	else if ((command[0] == '0') || (command[0] == 'F') || (command[0] == 'f') || (command[0] == 'n'))
	{
		m_state = false;
		strcpy(reply, " OK");
		reply[0] = command[0];
		reply_length = strlen(reply);
	}
	else if (command[0] == 'R')
	{
		this->reset();
		strcpy(reply, "ROK");
		reply_length = strlen(reply);
	}
	else
	{
		reply[0] = '?';
		reply_length = 1;
	}

	return reply_length;
}
