#include "raat.hpp"

#include "hx711-raat.hpp"

HX711RAAT::HX711RAAT(uint8_t dout_pin, uint8_t sck_pin, bool tare_at_boot) :
    m_dout_pin(dout_pin), m_sck_pin(sck_pin), m_tare_at_boot(tare_at_boot)
{
    m_scale_location.size = sizeof(float);
    raat_nv_alloc(m_scale_location);
}

void HX711RAAT::tick()
{
    if (m_tare_at_boot)
    {
        this->tare();
        m_tare_at_boot = false;
    }
}

void HX711RAAT::reset()
{

}

bool HX711RAAT::get_scaled(long& reading)
{
    bool success = m_loadcell.wait_ready_timeout(1000);
    if (success)
    {
        reading = m_loadcell.get_units();
    }
    return success;
}

long HX711RAAT::get_scaled(void)
{
    long reading = 0L;
    if (m_loadcell.wait_ready_timeout(1000))
    {
        reading = m_loadcell.get_units();
    }
    return reading;
}

bool HX711RAAT::get_raw(long& reading)
{
    bool success = m_loadcell.wait_ready_timeout(1000);
    if (success)
    {
        reading = m_loadcell.get_value();
    }
    return success;
}

long HX711RAAT::get_raw(void)
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

    raat_nv_load(&m_scale, m_scale_location);

    m_loadcell.set_scale(m_scale);
}

void HX711RAAT::tare(void)
{
    m_loadcell.tare();
}

void HX711RAAT::set_scale(float new_scale)
{
    m_scale = new_scale;
    raat_nv_save(&m_scale, m_scale_location);
    m_loadcell.set_scale(m_scale); 
}

uint16_t HX711RAAT::command_handler(char const * const command, char * reply)
{
    if (strncmp(command, "RAW?", 4) == 0)
    {
        long reading;
        if (this->get_raw(reading))
        {
            sprintf(reply, "%ld", reading);
        }
        else
        {
            sprintf(reply, "Err");   
        }
    }
    else if (strncmp(command, "SCALED?", 7) == 0)
    {
        long reading;
        if (this->get_scaled(reading))
        {
            sprintf(reply, "%ld", reading);
        }
        else
        {
            sprintf(reply, "Err");   
        }
    }
    else if (strncmp(command, "SET?", 4) == 0)
    {
        float fScale = m_loadcell.get_scale();
        long lScaleWhole = (long)fScale;
        long lScaleDecimals = (long)((fScale * 100) - (lScaleWhole * 100));

        sprintf(reply, "Scale: %ld.%ld, Offset: %ld", lScaleWhole, lScaleDecimals, m_loadcell.get_offset());
    }
    else if (strncmp(command, "TARE", 4) == 0)
    {
        this->tare();
        sprintf(reply, "OK");
    }
    else if (strncmp(command, "SCALE", 5) == 0)
    {
        int32_t scale_value;
        if (raat_parse_single_numeric(command+5, scale_value, NULL))
        {
            if (scale_value > 0)
            {
                long current_value = this->get_raw();

                this->set_scale(float(current_value) / float(scale_value));

                sprintf(reply, "OK");
            }
            else
            {
                sprintf(reply, "VAL?");
            }
        }
        else
        {
            sprintf(reply, "VAL?");
        }
    }
    else if (strncmp(command, "RST", 3) == 0)
    {
        this->set_scale(1.0f);
        sprintf(reply, "OK");
    }
    return strlen(reply);
}
