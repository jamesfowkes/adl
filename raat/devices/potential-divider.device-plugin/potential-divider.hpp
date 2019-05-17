#ifndef _POTENTIAL_DIVIDER_H_
#define _POTENTIAL_DIVIDER_H_

enum divider_type
{
    FIXED_PULLDOWN,
    FIXED_PULLUP
};
typedef enum divider_type DIVIDER_TYPE;

class PotentialDivider : public DeviceBase
{
public:
    PotentialDivider(int pin, uint32_t rDivider, DIVIDER_TYPE eDividerType);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    float resistance();
private:
    int m_pin;
    uint16_t m_maxAdcReading;
    uint32_t m_rDivider;
    DIVIDER_TYPE m_eDividerType;
};

#endif