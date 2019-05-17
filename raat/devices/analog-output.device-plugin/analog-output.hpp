#ifndef _ANALOG_OUTPUT_H_
#define _ANALOG_OUTPUT_H_

class AnalogOutput : public DeviceBase
{
public:
    AnalogOutput(int pin, int limit_min=0, int limit_max=255, int reset_level=0);
    void setup();
    void reset();
    void tick() {}
    uint16_t command_handler(char const * const command, char * reply);
    
private:
    int m_pin;
    int m_limit_min;
    int m_limit_max;
    int m_setting;
    int m_reset_level;

};

#endif