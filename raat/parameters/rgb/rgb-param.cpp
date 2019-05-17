/*
 * C++/Arduino Includes
 */

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS 
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

#include "raat-util-limited-range-int.hpp"
#include "rgb-param.hpp"

#define RGB_FORMAT "%" PRIi32 ",%" PRIi32 ",%" PRIi32

RGBParam::RGBParam(uint16_t limit, uint16_t r_default, uint16_t g_default, uint16_t b_default,
    bool clip_on_out_of_range, bool use_eeprom) :
    ParameterBase(use_eeprom, sizeof(uint16_t)*3),
    m_rgb{
        {r_default, 0, limit, clip_on_out_of_range},
        {g_default, 0, limit, clip_on_out_of_range},
        {b_default, 0, limit, clip_on_out_of_range}
    },
    m_defaults{r_default, g_default, b_default},
    m_clip(clip_on_out_of_range)
{
}

void RGBParam::reset()
{
    m_rgb[0].set(m_defaults[0]);
    m_rgb[1].set(m_defaults[1]);
    m_rgb[2].set(m_defaults[2]);
    this->on_change();
}

void RGBParam::setup() { ParameterBase::setup(); }

uint16_t RGBParam::get(eRGB index)
{
    return (uint16_t)m_rgb[index].value();
}

void RGBParam::get(uint16_t rgb[3])
{
    rgb[0] = (uint16_t)m_rgb[0].value();
    rgb[1] = (uint16_t)m_rgb[1].value();
    rgb[2] = (uint16_t)m_rgb[2].value();
}

bool RGBParam::set(uint16_t r, uint16_t g, uint16_t b)
{
    bool ok = true;
    ok &= m_rgb[0].set(r);
    ok &= m_rgb[1].set(g);
    ok &= m_rgb[2].set(b);
    this->on_change();
    return ok;
}

bool RGBParam::set(uint16_t rgb[3])
{
    return this->set(rgb[0], rgb[1], rgb[2]);
}

uint16_t RGBParam::command_handler(char const * const command, char * reply)
{
    int32_t rgb[3];

    int reply_length = 0;

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
                return sprintf(reply, RGB_FORMAT " (clipped)", m_rgb[0].value(), m_rgb[1].value(), m_rgb[2].value());
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
        sprintf(reply, RGB_FORMAT, m_rgb[0].value(), m_rgb[1].value(), m_rgb[2].value());
        reply_length = strlen(reply);
    }

    return reply_length;
}

void RGBParam::save()
{
    uint16_t rgb[3];
    if (m_use_eeprom)
    {
        rgb[0] = m_rgb[0].value();
        rgb[1] = m_rgb[1].value();
        rgb[2] = m_rgb[2].value();
        raat_nv_save(rgb, m_eeprom_location);
    }
}

void RGBParam::load()
{
    uint16_t rgb[3];
    if (m_use_eeprom)
    {
        raat_nv_load(rgb, m_eeprom_location);
        (void)this->set(rgb[0], rgb[1], rgb[2]);
    }
}
