#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP4725.h>

#include "adl-defs.h"
#include "adl-nv.h"
#include "parameter.h"
#include "device.h"
#include "adl-util.h"
#include "adl.h"

#include "adafruit-mcp4725.h"

/*
 * Class Private Functions
 */

uint8_t Adafruit_MCP4725ADL::handle_set_voltage_command(char const * const command, char * reply)
{
    int32_t voltage_mv;
    bool ok = false;

    if ((ok = adl_parse_single_numeric(&command[1], voltage_mv, NULL)))
    {
        if (ok = this->set_voltage(voltage_mv, false))
        {
            strcpy(reply, "VOK");            
        }
    }

    if (ok)
    {
        return strlen(reply);
    }
    else
    {
        strcpy(reply, "V?");
        return 2;
    }
}

uint8_t Adafruit_MCP4725ADL::handle_save_command(char const * const command, char * reply)
{
    if (this->set_voltage(m_last_value, true))
    {
        strcpy(reply, "SOK");
        return strlen(reply);
    }
    else
    {
        strcpy(reply, "S?");
        return 2;
    }
}

/*
 * Class Public Functions
 */

Adafruit_MCP4725ADL::Adafruit_MCP4725ADL(uint8_t i2c_addr, int32_t default_setting, uint16_t min, uint16_t max):
    m_dac(), m_i2c_addr(i2c_addr), m_last_value(-1), m_default(default_setting), m_min(min), m_max(max)
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
    this->set_voltage(m_default, false);
}

int Adafruit_MCP4725ADL::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    switch(command[0])
    {
    case 'V':
        reply_length = handle_set_voltage_command(command, reply);
        break;
    case 'S':
        reply_length = handle_save_command(command, reply);
        break;
    default:
        break;
    }

    if (reply_length == 0)
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

bool Adafruit_MCP4725ADL::set_voltage(int32_t voltage, bool save_to_device_eeprom)
{
    bool valid = (voltage >= m_min) && (voltage <= m_max);

    if (valid)
    {
        m_last_value = voltage;
        m_dac.setVoltage(voltage, save_to_device_eeprom);    
    }

    return valid;
}