#include "raat.hpp"

#include "hx711-raat.hpp"

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

bool HX711RAAT::get(long& reading)
{
    bool success = m_loadcell.wait_ready_timeout(1000);
    if (success)
    {
        reading = m_loadcell.get_value();
    }
    return success;
}

long HX711RAAT::get(void)
{
    long reading = 0L;
    if (m_loadcell.wait_ready_timeout(1000))
    {
        reading = m_loadcell.get_value();
    }
    return reading;
}

void HX711RAAT::setup()
{
    this->reset();
    m_loadcell.begin(m_dout_pin, m_sck_pin);
}

void HX711RAAT::tare(void)
{
    m_loadcell.tare();
}

uint16_t HX711RAAT::command_handler(char const * const command, char * reply)
{
    if (command[0] == '?')
    {
        long reading;
        if (this->get(reading))
        {
            sprintf(reply, "%lu", reading);
        }
        else
        {
            sprintf(reply, "Err");   
        }
    }
    else if (strncmp(command, "TARE", 4) == 0)
    {
        this->tare();
        sprintf(reply, "OK");
    }
    else if (strncmp(command, "SCALE", 5) == 0)
    {
        this->tare();
        sprintf(reply, "OK");
    }
    return strlen(reply);
}
