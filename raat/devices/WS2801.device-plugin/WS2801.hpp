#ifndef _WS2801_H_
#define _WS2801_H_

#include <Adafruit_WS2801.h>

#include "rgb-param.hpp"

class WS2801 : public DeviceBase
{
public:
    WS2801(uint8_t data_pin, uint8_t clock_pin, uint16_t npixels);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    Adafruit_WS2801& pixels();
    void set_pixels(uint8_t range_min, uint8_t range_max, RGBParam<uint8_t>& param);
    void set_pixels(uint8_t range_min, uint8_t range_max, uint8_t r, uint8_t g, uint8_t b);
    void set_pixels(uint8_t range_min, uint8_t range_max, const uint8_t rgb[3]);
    uint8_t npixels();
    void setPixelColor(uint16_t n, RGBParam<uint8_t>& param);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    void setPixelColor(uint16_t n, uint32_t c);
    void show();
    void clear();
private:
    int handle_command(char const * const command, char * reply);
    Adafruit_WS2801 m_pixels;
    uint8_t m_npixels;
};

#endif