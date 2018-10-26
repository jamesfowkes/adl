/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "potential-divider.h"
#include "thermistor.h"

static const float s_T0CinKelvin = 273.15f; 
static const float s_T25CinKelvin = s_T0CinKelvin + 25.0f;

Thermistor::Thermistor(uint8_t m_pin, uint32_t R25, uint16_t beta, uint32_t other_r, DIVIDER_TYPE eDividerType) :
    m_potential_divider(m_pin, other_r, eDividerType), m_beta(beta)
{
    //Rinf = R25 * exp(-B/T0) = R25 / exp(B/T0)
    m_Rinf = R25/exp(m_beta / s_T25CinKelvin);
}

void Thermistor::reset() {}
void Thermistor::tick() {}

void Thermistor::setup()
{
    m_potential_divider.setup();
}

unsigned int Thermistor::resistance()
{
    return m_potential_divider.resistance();
}

float Thermistor::reading()
{
    float t = m_beta / log(m_potential_divider.resistance() / m_Rinf);
    return t - s_T0CinKelvin;
}

int Thermistor::command_handler(char const * const command, char * reply)
{
    (void)command;
    sprintf(reply, "%.2f", this->reading());
    return strlen(reply);
}
