#include "raat.h"

#include "sevenseg.h"

static const uint16_t PROGMEM DIGIT_TO_SEGMENT_MAP[] = 
{
    // Bitmap from 0 to 15
    // 1 = segment is on for this digit
    0b1011010111101011, // A
    0b1111100111100100, // B
    0b1101111111110100, // C
    0b1011011010011110, // D
    0b1010001010111111, // E
    0b1000111011111011, // F
    0b0011111011110111  // G
};

SevenSeg::SevenSeg(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t dp)
{
    this->m_map.A = (1 << a);
    this->m_map.B = (1 << b);
    this->m_map.C = (1 << c);
    this->m_map.D = (1 << d);
    this->m_map.E = (1 << e);
    this->m_map.F = (1 << f);
    this->m_map.G = (1 << g);
    this->m_map.DP = (1 << dp);
}

void SevenSeg::reset() {}

void SevenSeg::setup()
{
    this->reset();
}

uint8_t SevenSeg::get_bitmap_for_digit(uint8_t digit, bool tails, bool dp)
{
    uint8_t display = 0;
    
    if (digit < 16)
    {
        uint16_t digit_bit = (1 << (15-digit));

        display |= (DIGIT_TO_SEGMENT_MAP[0] & digit_bit) ? this->m_map.A : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[1] & digit_bit) ? this->m_map.B : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[2] & digit_bit) ? this->m_map.C : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[3] & digit_bit) ? this->m_map.D : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[4] & digit_bit) ? this->m_map.E : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[5] & digit_bit) ? this->m_map.F : 0;
        display |= (DIGIT_TO_SEGMENT_MAP[6] & digit_bit) ? this->m_map.G : 0;
    }

    if (tails)
    {
        if (digit == 6) { display |= this->m_map.A; }
        if (digit == 9) { display |= this->m_map.D; }
    }

    if (dp)
    {
        display |= this->m_map.DP;
    }

    return display;
}
