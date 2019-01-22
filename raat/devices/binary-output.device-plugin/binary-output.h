#ifndef _BINARY_OUTPUT_H_
#define _BINARY_OUTPUT_H_

static const uint8_t PIN_NOT_USED = 0xFF;

class BinaryOutput : public DeviceBase
{
public:
    BinaryOutput(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    void set(uint8_t value);
    void tristate();

private:
    uint8_t m_pins[8];
    uint8_t m_npins;
    uint8_t m_max_value;
};

#endif
