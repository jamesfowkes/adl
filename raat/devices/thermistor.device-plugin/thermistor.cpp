/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

#include "potential-divider.hpp"
#include "thermistor.hpp"

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

float Thermistor::resistance()
{
    return m_potential_divider.resistance();
}

float Thermistor::reading()
{
    float r = m_potential_divider.resistance();
    float t = m_beta / log(r / m_Rinf);
    return t - s_T0CinKelvin;
}

int Thermistor::command_handler(char const * const command, char * reply)
{
    (void)command;
    float readingx100 = this->reading() * 100.0f;

    int8_t whole = ((int16_t)(readingx100) / 100);
    int8_t decimal = ((int16_t)(readingx100 - (whole*100)));

    sprintf(reply, "%d.%d", whole, decimal);
    return strlen(reply);
}
