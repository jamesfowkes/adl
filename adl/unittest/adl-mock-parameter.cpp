#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "device.h"
#include "parameter.h"

#include "adl.h"
#include "protocol.h"

class TestParam : public ParameterBase
{
    void reset() {};
    void setup() {};
    int command_handler(char const * const command, char * reply) { (void)command; (void)reply; return 0;};
};
static TestParam s_mock_param;

ParameterBase& adl_get_param(DEVICE_ADDRESS address) {(void)address; return s_mock_param; }

static int test_param_cmd_handler(char const * const command, char * reply) {(void)command; (void)reply; return 0;}

COMMAND_HANDLER& adl_get_param_cmd_handler(PARAM_ADDRESS address) { (void)address; return test_param_cmd_handler; }
