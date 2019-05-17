#ifndef _8BIT_RGB_PARAM_H_
#define _8BIT_RGB_PARAM_H_

#include "raat-util-limited-range-int.hpp"

typedef enum _eRGB
{
    eR, eG, eB
} eRGB;


class EightBitRGBParam : public ParameterBase
{
public:
    EightBitRGBParam(uint8_t limit, uint8_t r_default, uint8_t g_default, uint8_t b_default,
        bool clip_on_out_of_range, bool use_eeprom);
    void setup();
    void reset();
    uint16_t command_handler(char const * const command, char * reply);
    
    bool set(uint8_t rgb[3]);
    bool set(uint8_t r, uint8_t g, uint8_t b);
    uint8_t get(eRGB index);
    void get(uint8_t rgb[3]);

    void save();
    void load();

private:

    LimitedRangeInt<uint8_t> m_rgb[3];
    uint8_t m_defaults[3];
    bool m_clip;
};

#endif
