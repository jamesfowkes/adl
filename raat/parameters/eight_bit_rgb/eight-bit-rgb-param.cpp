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
#include "eight-bit-rgb-param.hpp"

#define RGB_FORMAT "%" PRIu8 ",%" PRIu8 ",%" PRIu8

EightBitRGBParam::EightBitRGBParam(uint8_t limit, uint8_t r_default, uint8_t g_default, uint8_t b_default,
    bool clip_on_out_of_range, bool use_eeprom) :
    ParameterBase(use_eeprom, sizeof(uint8_t)*3),
    m_rgb{
        {r_default, 0, limit, clip_on_out_of_range},
        {g_default, 0, limit, clip_on_out_of_range},
        {b_default, 0, limit, clip_on_out_of_range}
    },
    m_defaults{r_default, g_default, b_default},
    m_clip(clip_on_out_of_range)
{
}

void EightBitRGBParam::reset()
{
    m_rgb[0].set(m_defaults[0]);
    m_rgb[1].set(m_defaults[1]);
    m_rgb[2].set(m_defaults[2]);
    this->on_change();
}

void EightBitRGBParam::setup() { ParameterBase::setup(); }

uint8_t EightBitRGBParam::get(eRGB index)
{
    return (uint8_t)m_rgb[index].value();
}

void EightBitRGBParam::get(uint8_t rgb[3])
{
    rgb[0] = (uint8_t)m_rgb[0].value();
    rgb[1] = (uint8_t)m_rgb[1].value();
    rgb[2] = (uint8_t)m_rgb[2].value();
}

bool EightBitRGBParam::set(uint8_t r, uint8_t g, uint8_t b)
{
    bool ok = true;
    ok &= m_rgb[0].set(r);
    ok &= m_rgb[1].set(g);
    ok &= m_rgb[2].set(b);
    this->on_change();
    return ok;
}

bool EightBitRGBParam::set(uint8_t rgb[3])
{
    return this->set(rgb[0], rgb[1], rgb[2]);
}

uint16_t EightBitRGBParam::command_handler(char const * const command, char * reply)
{
    int32_t rgb[3];

    int reply_length = 0;

    if (command[0] == 'S')
    {
        uint8_t parsed_count = raat_parse_comma_separated_numerics(&command[1], rgb);

        if (parsed_count == 3)
        {
            if (this->set((uint8_t)rgb[0], (uint8_t)rgb[1], (uint8_t)rgb[2]))
            {
                return sprintf(reply, RGB_FORMAT, (uint8_t)rgb[0], (uint8_t)rgb[1], (uint8_t)rgb[2]);
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

void EightBitRGBParam::save()
{
    uint8_t rgb[3];
    if (m_use_eeprom)
    {
        rgb[0] = m_rgb[0].value();
        rgb[1] = m_rgb[1].value();
        rgb[2] = m_rgb[2].value();
        raat_nv_save(rgb, m_eeprom_location);
    }
}

void EightBitRGBParam::load()
{
    uint8_t rgb[3];
    if (m_use_eeprom)
    {
        raat_nv_load(rgb, m_eeprom_location);
        (void)this->set(rgb[0], rgb[1], rgb[2]);
    }
}
