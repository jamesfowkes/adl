#ifndef _RAAT_SEVENSEG_H_
#define _RAAT_SEVENSEG_H_

typedef struct _seven_segment_map
{
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;
    uint8_t G;
    uint8_t DP;
} seven_segment_map;

class SevenSeg
{
public:
    SevenSeg(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t dp);
    void setup();
    void reset();
    
    uint8_t get_bitmap_for_digit(uint8_t digit, bool tails, bool dp);

private:
    seven_segment_map m_map;
};
#endif