#ifndef _MCP41XXX_H_
#define _MCP41XXX_H_

#include "Arduino.h"


class MCP41XXX  : public DeviceBase
{
public:
    MCP41XXX(uint8_t cs_pin);
    void setup();
    void reset();
    uint16_t command_handler(char const * const command, char * reply);
    void tick();
    void set_wiper(uint8_t position);
    uint8_t handle_set_wiper_command(char const * const command, char * reply);
    
private:
    uint8_t m_cs_pin;
};

#endif
