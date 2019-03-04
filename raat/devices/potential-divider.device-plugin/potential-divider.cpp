#include <float.h>

#include "raat.hpp"

#include "potential-divider.hpp"

PotentialDivider::PotentialDivider(int pin, uint32_t rDivider, DIVIDER_TYPE eDividerType) : 
    m_pin(pin), m_rDivider(rDivider), m_eDividerType(eDividerType)
{
    m_maxAdcReading = raat_board_max_adc_reading();
}

void PotentialDivider::reset() {}
void PotentialDivider::tick() {}

void PotentialDivider::setup()
{
    pinMode(m_pin, INPUT);
}

float PotentialDivider::resistance()
{
    uint16_t adc = analogRead(m_pin);
    float resistance = 0;

    switch(m_eDividerType)
    {
    case FIXED_PULLDOWN:
        if (adc == 0)
        {
            resistance = FLT_MAX;
        }
        else
        {
            resistance = m_rDivider * m_maxAdcReading;
            resistance = resistance / adc;
            resistance -= m_rDivider;
        }
        break;
    case FIXED_PULLUP:
        resistance = m_rDivider * adc / (m_maxAdcReading - adc);
        break;
    default:
        break;
    }
    return resistance;
}

int PotentialDivider::command_handler(char const * const command, char * reply)
{
    (void)command;
    unsigned int value = analogRead(m_pin);
    sprintf(reply, "%u", value);
    return strlen(reply);
}
