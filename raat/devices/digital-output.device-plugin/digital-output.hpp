#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

class DigitalOutput : public DeviceBase
{
public:
    DigitalOutput(int pin);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    void set(bool on);
    bool state(void);
    void tristate();

private:
    int m_pin;
};

#endif
