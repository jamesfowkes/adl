#ifndef _RAAT_LED_EFFECT_H_
#define _RAAT_LED_EFFECT_H_

class LarsonScanner
{
public:
    LarsonScanner(uint8_t n_strip_leds, uint8_t n_larson_leds);

    void setup();
    void reset();
    void tick();

    void start(uint8_t r, uint8_t g, uint8_t b);
    void get(uint8_t * dst);
private:
    uint8_t m_n_strip_leds;
    uint8_t m_n_larson_leds;
};
#endif