#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP4725.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"

#include "adafruit-mcp4725.h"

static bool command_is_query(char const * const command)
{
    int command_length = strlen(command);
    return command[command_length-1] == '?';
}

static bool command_is_voltage_setting(char const * const command)
{
    return (command[0] == 'V')
}

/*
 * Class Private Functions
 */

uint8_t Adafruit_MCP4725ADL::handle_query_command(char const * const command, char * reply)
{
    reply[0] = '?';
    return 1;
}

uint8_t Adafruit_MCP4725ADL::handle_setting_command(char const * const command, char * reply)
{
    int32_t voltage_mv;
    bool ok = false;

    if (ok = adl_parse_single_numeric(&command[1], voltage_mv, NULL);)
    {
        if (ok = voltage_mv <= 0x0FFF)
        {
            m_dac.setVoltage(voltage_mv);
            strcpy(reply, "VOK");            
        }
    }

    if (ok)
    {
        return strlen(reply);
    }
    else
    {
        reply[0] = '?';
        return 1;
    }
}

/*
 * Class Public Functions
 */

Adafruit_MCP4725ADL::Adafruit_MCP4725ADL(uint8_t i2c_addr) : m_dac(0,0), m_i2c_addr(i2c_addr)
{
    
}

void Adafruit_MCP4725ADL::reset()
{
    
}

void Adafruit_MCP4725ADL::tick()
{

}

void Adafruit_MCP4725ADL::setup()
{
    this->reset();
    m_dac.begin(m_i2c_addr);
}

int Adafruit_MCP4725ADL::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;

    if (command_is_query(command))
    {
        reply_length = handle_query_command(command, reply);
    }
    else if (command_is_voltage_setting(command))
    {
        reply_length = handle_setting_command(command, reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}
