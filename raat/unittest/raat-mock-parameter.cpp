#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "raat.hpp"
#include "protocol.hpp"

TestParam::TestParam() : ParameterBase(true,sizeof(int32_t)) {}

uint16_t TestParam::command_handler(char const * const command, char * reply)
{
	strncpy(m_last_command, command, 128);
	printf("TestParam1 got command %s", reply);
	return strlen(reply);
}

static TestParam s_mock_param1;
static TestParam s_mock_param2;

static ParameterBase * s_params[] = {
	&s_mock_param1,
	&s_mock_param2
};

ParameterBase& raat_get_param(DEVICE_ADDRESS address)
{
	return *s_params[address-1];
}

static int test_param_cmd_handler(char const * const command, char * reply) {(void)command; (void)reply; return 0;}
static COMMAND_HANDLER test_command_handlers[] = {test_param_cmd_handler};

COMMAND_HANDLER& raat_get_param_cmd_handler(PARAM_ADDRESS address) {
	return test_command_handlers[address-1];
}
