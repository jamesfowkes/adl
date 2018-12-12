#include "adl.h"

#include "MAX7219.h"
#include "MAX7219-8x8.h"

/*
 * Class Private Functions
 */

/*
 * Class Public Functions
 */

MAX7219_8x8::MAX7219_8x8(uint8_t cs, uint8_t din, uint8_t dclk, uint8_t device_count) :
  m_max7219(cs, din, dclk, device_count)
{
    this->m_max7219.set_decode(eDecodeMode_None);
    this->m_max7219.set_scan_limit(7);
}

void MAX7219_8x8::reset()
{
    this->m_max7219.reset();
}

void MAX7219_8x8::tick()
{
    this->m_max7219.tick();
}

void MAX7219_8x8::setup()
{
    this->reset();
}

int MAX7219_8x8::command_handler(char const * const command, char * reply)
{
    (void)command; (void)reply;
    int reply_length = 0;
    return reply_length;
}

void MAX7219_8x8::set(uint8_t row, uint8_t col, bool set)
{
    uint8_t device = col / 8;
    uint8_t data = this->m_max7219.get(device, row);

    if (set)
    {
        data |= (1 << (col % 8));
    }
    else
    {
        data &= ~(1 << (col % 8));
    }

    this->m_max7219.set(device, row, data);
}

void MAX7219_8x8::clear_all()
{
    this->m_max7219.clear_all();
}

void MAX7219_8x8::update()
{
    this->m_max7219.update();
}

void MAX7219_8x8::set_intensity(uint8_t intensity)
{
    this->m_max7219.set_intensity(intensity);
}

void MAX7219_8x8::set_shutdown(bool shdn)
{
    this->m_max7219.set_shutdown(shdn);
}

void MAX7219_8x8::set_test(bool test)
{
    this->m_max7219.set_test(test);
}
