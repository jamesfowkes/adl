#ifndef _THERMISTOR_H_
#define _THERMISTOR_H_

#include "potential-divider.hpp"

class Thermistor : public DeviceBase
{
public:
    Thermistor(uint8_t m_pin, uint32_t R25, uint16_t beta, uint32_t other_r, DIVIDER_TYPE eDividerType);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    float resistance();
    float reading();
    
private:
    PotentialDivider m_potential_divider;
    float m_beta;
    float m_Rinf;
};

#endif