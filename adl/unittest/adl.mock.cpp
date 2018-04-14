#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "device.h"
#include "parameter.h"

#include "adl.h"
#include "protocol.h"

unsigned long millis() { return 0; }

class TestDevice : public DeviceBase
{
    void reset() {};
    void setup() {};
    int command_handler(char const * const command, char * reply) { (void)command; (void)reply; return 0;};
};
static TestDevice s_test_device;

class TestParam : public ParameterBase
{
    void reset() {};
    void setup() {};
    int command_handler(char const * const command, char * reply) { (void)command; (void)reply; return 0;};
};
static TestParam s_test_param;

DeviceBase& adl_get_device(DEVICE_ADDRESS address) {(void)address; return s_test_device; }
ParameterBase& adl_get_param(DEVICE_ADDRESS address) {(void)address; return s_test_param; }

static int test_device_cmd_handler(char const * const command, char * reply) {(void)command; (void)reply; return 0;}
static int test_param_cmd_handler(char const * const command, char * reply) {(void)command; (void)reply; return 0;}
static COMMAND_HANDLER test_command_handlers[] = {test_device_cmd_handler, test_param_cmd_handler};

COMMAND_HANDLER& adl_get_device_cmd_handler(DEVICE_ADDRESS address) { (void)address; return test_command_handlers[0]; }
COMMAND_HANDLER& adl_get_param_cmd_handler(PARAM_ADDRESS address) { (void)address; return test_command_handlers[1]; }

void adl_board_send(char * to_send) {(void)to_send;}
