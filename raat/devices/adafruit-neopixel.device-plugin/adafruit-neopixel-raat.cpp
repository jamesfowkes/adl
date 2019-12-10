#include <Adafruit_NeoPixel.h>

#include "raat.hpp"

#include "adafruit-neopixel-raat.hpp"

/*
 * Class Private Functions
 */

static bool valid_rgb_value(int32_t val)
{
    return (val >= 0) && (val <= 255);
}

static bool valid_rgb_values(int32_t(&rgb)[3])
{
    return valid_rgb_value(rgb[0]) && valid_rgb_value(rgb[1]) && valid_rgb_value(rgb[2]);
}

/*
 * Class RAAT Functions
 */

void AdafruitNeoPixelRAAT::set_pixels(uint8_t range_min, uint8_t range_max, RGBParam<uint8_t>& param)
{
    uint8_t rgb[3];
    param.get(rgb);
    this->setPixelColor(range_min, range_max, (uint8_t)rgb[0], (uint8_t)rgb[1], (uint8_t)rgb[2]);
}

void AdafruitNeoPixelRAAT::set_pixels(uint8_t range_min, uint8_t range_max, uint8_t r, uint8_t g, uint8_t b)
{
    if (range_min < range_max)
    {
        for (uint8_t i=range_min; i<range_max+1; i++)
        {
            m_pixels.setPixelColor(i, r, g, b);
        }
    }
}

void AdafruitNeoPixelRAAT::set_pixels(uint8_t range_min, uint8_t range_max, const uint8_t rgb[3])
{
    this->set_pixels(range_min, range_max, rgb[0], rgb[1], rgb[2]);
}

int AdafruitNeoPixelRAAT::handle_command(char const * const command, char * reply)
{
    int32_t rgb[3];

    int32_t range_min;
    int32_t range_max;

    char * end_of_range = NULL;

    bool valid_range = raat_convert_numeric_range(command, range_min, range_max, &end_of_range);
    valid_range &= range_min < this->m_npixels;
    valid_range &= range_max < this->m_npixels;

    if (valid_range && (*end_of_range == ':'))
    {
        end_of_range++;        
        uint8_t parsed_count = raat_parse_comma_separated_numerics(end_of_range, rgb);

        if (parsed_count == 3)
        {
            if (valid_rgb_values(rgb))
            {
                this->set_pixels(range_min, range_max, rgb[0], rgb[1], rgb[2]);
                this->show();
                return sprintf(reply, "%u-%u: %u,%u,%u",
                    (uint8_t)range_min, (uint8_t)range_max,
                    (uint8_t)rgb[0], (uint8_t)rgb[1], (uint8_t)rgb[2]);

            }
            else
            {
                return raat_msg_invalid_values(reply);
            }
        }
        else
        {
            return raat_msg_wrong_number_of_values(reply, parsed_count, end_of_range);
        }
    }
    else
    {
        return raat_msg_invalid_range(reply);
    }
}

void AdafruitNeoPixelRAAT::setPixelColor(uint16_t n, RGBParam<uint8_t>& param)
{
    uint8_t rgb[3];
    param.get(rgb);
    this->setPixelColor(n, (uint8_t)rgb[0], (uint8_t)rgb[1], (uint8_t)rgb[2]);
}

void AdafruitNeoPixelRAAT::setPixelColor(uint16_t n, uint8_t * pRGB)
{
    if (pRGB)
    {
        m_pixels.setPixelColor(n, pRGB[0], pRGB[1], pRGB[2]);   
    }
}

void AdafruitNeoPixelRAAT::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
    m_pixels.setPixelColor(n, r, g, b);
}

void AdafruitNeoPixelRAAT::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    m_pixels.setPixelColor(n, r, g, b, w);
}

void AdafruitNeoPixelRAAT::setPixelColor(uint16_t n, uint32_t c)
{
    m_pixels.setPixelColor(n, c);
}

void AdafruitNeoPixelRAAT::show()
{
    m_pixels.show();   
}

void AdafruitNeoPixelRAAT::clear()
{
    m_pixels.clear();   
}

/*
 * Class RAAT Functions
 */

AdafruitNeoPixelRAAT::AdafruitNeoPixelRAAT(uint8_t pin, uint16_t npixels, uint16_t type) : 
    m_pixels(npixels,pin,type), m_npixels(npixels)
{
    m_pixels.begin();
}

void AdafruitNeoPixelRAAT::reset()
{
    m_pixels.clear();
    m_pixels.show();
}

void AdafruitNeoPixelRAAT::tick()
{

}

void AdafruitNeoPixelRAAT::setup()
{
    this->reset();
}

uint16_t AdafruitNeoPixelRAAT::command_handler(char const * const command, char * reply)
{
    int reply_length;

    if (command[0] == 'R')
    {
        this->reset();
        strcpy(reply, "ROK");
        reply_length = strlen(reply);
    }
    else
    {
        reply_length = handle_command(command, reply);
    }

    return reply_length;
}

Adafruit_NeoPixel& AdafruitNeoPixelRAAT::pixels()
{
    return m_pixels;
}

uint8_t AdafruitNeoPixelRAAT::npixels()
{
    return m_npixels;
}
