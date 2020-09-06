#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

class DigitalInput : public DeviceBase
{
public:
    DigitalInput(uint8_t pin);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    bool state();

    uint8_t pin();

private:
    uint8_t m_pin;

};

#endif
