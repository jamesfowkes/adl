#ifndef _ANALOG_INPUT_H_
#define _ANALOG_INPUT_H_

class AnalogInput : public DeviceBase
{
public:
    AnalogInput(int pin);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    unsigned int reading();
private:
    int m_pin;
};

#endif