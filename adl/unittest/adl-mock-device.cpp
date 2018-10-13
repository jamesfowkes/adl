#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "device.h"
#include "parameter.h"

#include "adl.h"
#include "protocol.h"

class MockDevice : public DeviceBase
{
    void reset() {};
    void setup() {};
    void tick() {};
    int command_handler(char const * const command, char * reply) { (void)command; (void)reply; return 0;};
};
static MockDevice s_mock_device;

DeviceBase& adl_get_device(DEVICE_ADDRESS address) {(void)address; return s_mock_device; }

static int test_device_cmd_handler(char const * const command, char * reply) {(void)command; (void)reply; return 0;}
static COMMAND_HANDLER test_command_handlers[] = {test_device_cmd_handler};

COMMAND_HANDLER& adl_get_device_cmd_handler(DEVICE_ADDRESS address) { (void)address; return test_command_handlers[0]; }
