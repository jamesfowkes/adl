#ifndef _RGB_PARAM_H_
#define _RGB_PARAM_H_

#include "raat-util-limited-range-int.hpp"

typedef enum _eRGB
{
    eR, eG, eB
} eRGB;


class RGBParam : public ParameterBase
{
public:
    RGBParam(uint16_t limit, uint16_t r_default, uint16_t g_default, uint16_t b_default,
        bool clip_on_out_of_range, bool use_eeprom);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    
    bool set(uint16_t rgb[3]);
    bool set(uint16_t r, uint16_t g, uint16_t b);
    uint16_t get(eRGB index);
    void get(uint16_t rgb[3]);

    void save();
    void load();

private:

    LimitedRangeInt<uint16_t> m_rgb[3];
    uint16_t m_defaults[3];
    bool m_clip;
};

#endif
