#include "raat.hpp"

#include "hx711-RAAT.hpp"

HX711RAAT::HX711RAAT(uint8_t dout_pin, uint8_t sck_pin) :
    m_dout_pin(dout_pin), m_sck_pin(sck_pin)
{

}

void HX711RAAT::tick()
{
}

void HX711RAAT::reset()
{

}

void HX711RAAT::setup()
{
    this->reset();
}

uint16_t HX711RAAT::command_handler(char const * const command, char * reply)
{
    (void)command;
    (void)reply;
    return 0;
}
