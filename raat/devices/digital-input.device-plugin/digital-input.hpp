#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

class DigitalInput : public DeviceBase
{
public:
    DigitalInput(int pin);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    bool state();
private:
    int m_pin;
};

#endif
