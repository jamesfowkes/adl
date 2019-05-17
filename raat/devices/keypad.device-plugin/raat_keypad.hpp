#ifndef _RAAT_KEYPAD_H_
#define _RAAT_KEYPAD_H_

class RAATKeypad : public DeviceBase
{
public:
    RAATKeypad(Keypad& keypad);
    void setup();
    void reset();
    void tick();
    
    uint16_t command_handler(char const * const command, char * reply);

private:
    Keypad * m_pkeypad;
};

#endif
