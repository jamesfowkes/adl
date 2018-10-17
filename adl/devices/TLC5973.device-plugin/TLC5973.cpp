#include <Arduino.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"
#include "adl-util.h"
#include "adl-messages.h"

#include "TLC5973.h"

/*
 * Class Private Functions
 */

static bool valid_rgb_value(int32_t val)
{
    return (val >= 0) && (val <= 4095);
}

static bool valid_rgb_values(int32_t(&rgb)[3])
{
    return valid_rgb_value(rgb[0]) && valid_rgb_value(rgb[1]) && valid_rgb_value(rgb[2]);
}

void TLC5973::set_pixels(uint8_t range_min, uint8_t range_max, uint16_t r, uint16_t g, uint16_t b)
{
    for (uint8_t i=range_min; i<range_max+1; i++)
    {
        this->setPixelColor(i, r, g, b);
    }
    this->show();
}

#define NOP __asm__ __volatile__ ("nop\n\t"); __asm__ __volatile__ ("nop\n\t")

TLC5973::TLC5973(uint16_t n, uint8_t p) : m_npixels(n), m_pin(p)
{
    updateLength();
}

void TLC5973::updateLength()
{
    if(mp_pixels)
    {
        free(mp_pixels);
    }
    m_numWords = m_npixels * 3;
    if((mp_pixels = (uint16_t *)malloc(m_numWords)))
    {
        memset(mp_pixels, 0, m_numWords);
    }
    else
    {
        m_npixels = m_numWords = 0;
    } 
}

void TLC5973::setup(void)
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
    mp_port = portOutputRegister(digitalPinToPort(m_pin));
    m_pinMask = digitalPinToBitMask(m_pin);
    this->reset();
}

void TLC5973::reset()
{
    this->clear();
    this->show();
}

void TLC5973::tick()
{

}

int TLC5973::handle_command(char const * const command, char * reply)
{
    int32_t rgb[3];

    int32_t range_min;
    int32_t range_max;

    char * end_of_range = NULL;

    bool valid_range = adl_convert_numeric_range(command, range_min, range_max, &end_of_range);
    valid_range &= range_min < this->m_npixels;
    valid_range &= range_max < this->m_npixels;
    valid_range &= range_min >= 0;
    valid_range &= range_min >= 0;

    if (valid_range && (*end_of_range == ','))
    {
        end_of_range++;        
        uint8_t parsed_count = adl_parse_comma_separated_numerics(end_of_range, rgb);

        if (parsed_count == 3)
        {
            if (valid_rgb_values(rgb))
            {
                set_pixels(range_min, range_max, rgb[0], rgb[1], rgb[2]);
                return sprintf(reply, "%u-%u: %u,%u,%u",
                    (uint8_t)range_min, (uint8_t)range_max,
                    (uint16_t)rgb[0], (uint16_t)rgb[1], (uint16_t)rgb[2]);
            }
            else
            {
                return adl_msg_invalid_values(reply);
            }
        }
        else
        {
            return adl_msg_wrong_number_of_values(reply, parsed_count, end_of_range);
        }
    }
    else
    {
        return adl_msg_invalid_range(reply);
    }
}

int TLC5973::command_handler(char const * const command, char * reply)
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


void TLC5973::setPixelColor(uint16_t n, uint16_t r, uint16_t g, uint16_t b)
{
    if(n < m_npixels)
    {
        uint16_t *p;
        p = &mp_pixels[n * 3];    // 3 bytes per pixel
        p[2] = r;          // R,G,B always stored
        p[1] = g;
        p[0] = b;
    }
}

void TLC5973::clear()
{
    for(uint16_t i = 0; i < m_npixels; i++)
    {
        setPixelColor(i,0,0,0);
    }
}

void TLC5973::pulse() 
{
    *mp_port|=m_pinMask;
    *mp_port&=~m_pinMask;
}

void TLC5973::writeZero()
{
    pulse();
    NOP;
    NOP;
    NOP;
}

void TLC5973::writeNone()
{
    NOP;
    NOP;
    NOP;
    NOP;
    NOP;
}

void TLC5973::writeOne()
{
    pulse();
    pulse();
    NOP;
}

void TLC5973::waitGSLAT()
{
    writeNone();
    writeNone();
    writeNone();
    writeNone();
    writeNone();
    writeNone();
}

void TLC5973::writeWord(uint16_t word)
{
    unsigned char i;
    for(i = 0; i < 12; i++)
    {
        if(word & 0x800)
        {
            writeOne();
        }
        else
        {
            writeZero();
        }
        word <<= 1;
    }
}

void TLC5973::show()
{
    noInterrupts();
    for(uint16_t i = 0; i < m_numWords; i=i+3)
    {
        writeWord(0x03AA);
        writeWord(mp_pixels[i] );
        writeWord(mp_pixels[i+1] );
        writeWord(mp_pixels[i+2] );
        waitGSLAT();
    }
    waitGSLAT();
    interrupts();
}

