#ifndef _ADAFRUIT_MCP4725_RAAT_H_
#define _ADAFRUIT_MCP4725_RAAT_H_

class Adafruit_MCP4725RAAT : public DeviceBase
{
public:
    Adafruit_MCP4725RAAT(uint8_t i2c_address, int32_t default_setting, uint16_t min, uint16_t max);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    bool set_voltage(int32_t voltage, bool save);

private:
    Adafruit_MCP4725 m_dac;
    uint8_t m_i2c_addr;
    int32_t m_last_value;
    int32_t m_default;
    uint16_t m_min;
    uint16_t m_max;

    uint8_t handle_save_command(char const * const command, char * reply);
    uint8_t handle_set_voltage_command(char const * const command, char * reply);
};

#endif