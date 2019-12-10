#ifndef _RGB_PARAM_H_
#define _RGB_PARAM_H_

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

#include "raat-util-limited-range-int.hpp"

#define RGB_FORMAT "%" PRIi32 ",%" PRIi32 ",%" PRIi32

typedef enum _eRGB
{
    eR, eG, eB
} eRGB;

template <class INT_TYPE>
class RGBParam : public ParameterBase
{
public:
    RGBParam(INT_TYPE limit, INT_TYPE r_default, INT_TYPE g_default, INT_TYPE b_default,
        bool clip_on_out_of_range, bool use_eeprom);
    void setup();
    void reset();
    uint16_t command_handler(char const * const command, char * reply);
    
    bool set(INT_TYPE rgb[3]);
    bool set(INT_TYPE r, INT_TYPE g, INT_TYPE b);
    INT_TYPE get(eRGB index);
    void get(INT_TYPE rgb[3]);

    void save();
    void load();

private:

    LimitedRangeInt<INT_TYPE> m_rgb[3];
    INT_TYPE m_defaults[3];
    bool m_clip;
};

template <class INT_TYPE>
RGBParam<INT_TYPE>::RGBParam(INT_TYPE limit, INT_TYPE r_default, INT_TYPE g_default, INT_TYPE b_default,
    bool clip_on_out_of_range, bool use_eeprom) :
    ParameterBase(use_eeprom, sizeof(INT_TYPE)*3),
    m_rgb{
        {r_default, 0, limit, clip_on_out_of_range},
        {g_default, 0, limit, clip_on_out_of_range},
        {b_default, 0, limit, clip_on_out_of_range}
    },
    m_defaults{r_default, g_default, b_default},
    m_clip(clip_on_out_of_range)
{
}

template <class INT_TYPE>
void RGBParam<INT_TYPE>::reset()
{
    m_rgb[0].set(m_defaults[0]);
    m_rgb[1].set(m_defaults[1]);
    m_rgb[2].set(m_defaults[2]);
    this->on_change();
}

template <class INT_TYPE>
void RGBParam<INT_TYPE>::setup() { ParameterBase::setup(); }

template <class INT_TYPE>
INT_TYPE RGBParam<INT_TYPE>::get(eRGB index)
{
    return (INT_TYPE)m_rgb[index].value();
}

template <class INT_TYPE>
void RGBParam<INT_TYPE>::get(INT_TYPE rgb[3])
{
    rgb[0] = (INT_TYPE)m_rgb[0].value();
    rgb[1] = (INT_TYPE)m_rgb[1].value();
    rgb[2] = (INT_TYPE)m_rgb[2].value();
}

template <class INT_TYPE>
bool RGBParam<INT_TYPE>::set(INT_TYPE r, INT_TYPE g, INT_TYPE b)
{
    bool ok = true;
    ok &= m_rgb[0].set(r);
    ok &= m_rgb[1].set(g);
    ok &= m_rgb[2].set(b);
    this->on_change();
    return ok;
}

template <class INT_TYPE>
bool RGBParam<INT_TYPE>::set(INT_TYPE rgb[3])
{
    return this->set(rgb[0], rgb[1], rgb[2]);
}

template <class INT_TYPE>
uint16_t RGBParam<INT_TYPE>::command_handler(char const * const command, char * reply)
{
    int32_t rgb[3];

    uint16_t reply_length = 0;

    if (command[0] == 'S')
    {
        uint8_t parsed_count = raat_parse_comma_separated_numerics(&command[1], rgb);

        if (parsed_count == 3)
        {
            if (this->set(rgb[0], rgb[1], rgb[2]))
            {
                return sprintf(reply, RGB_FORMAT, rgb[0], rgb[1], rgb[2]);
            }
            else if (m_clip)
            {
                return sprintf(reply, RGB_FORMAT " (clipped)", 
                    (int32_t)m_rgb[0].value(), (int32_t)m_rgb[1].value(), (int32_t)m_rgb[2].value());
            }
            else
            {
                return raat_msg_invalid_values(reply);
            }
        }
        else
        {
            return raat_msg_wrong_number_of_values(reply, parsed_count, &command[1]);
        }
    }
    else if (command[0] == '?')
    {
        sprintf(reply, RGB_FORMAT, (int32_t)m_rgb[0].value(), (int32_t)m_rgb[1].value(), (int32_t)m_rgb[2].value());
        reply_length = strlen(reply);
    }

    return reply_length;
}

template <class INT_TYPE>
void RGBParam<INT_TYPE>::save()
{
    INT_TYPE rgb[3];
    if (m_use_eeprom)
    {
        rgb[0] = m_rgb[0].value();
        rgb[1] = m_rgb[1].value();
        rgb[2] = m_rgb[2].value();
        raat_nv_save(rgb, m_eeprom_location);
    }
}

template <class INT_TYPE>
void RGBParam<INT_TYPE>::load()
{
    INT_TYPE rgb[3];
    if (m_use_eeprom)
    {
        raat_nv_load(rgb, m_eeprom_location);
        (void)this->set(rgb[0], rgb[1], rgb[2]);
    }
}

#endif
