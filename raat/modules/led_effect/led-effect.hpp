#ifndef _RAAT_LED_EFFECT_H_
#define _RAAT_LED_EFFECT_H_

enum direction
{
	DIR_POS,
	DIR_NEG
};

class LarsonScanner
{
public:
    LarsonScanner(uint8_t * dst, uint8_t n_strip_leds, uint8_t n_larson_leds);

    void setup();
    void reset();
    void tick();

    void print(uint8_t * pleds);
    void print(uint8_t * pleds, uint8_t min_index, uint8_t max_index);

    void start(uint8_t r, uint8_t g, uint8_t b);
    void update();
private:

	void set_next();
	void clear_last_pixel();
	uint8_t * mp_leds;
	uint8_t * mp_values;
    uint8_t m_n_strip_leds;
    uint8_t m_n_larson_leds;
    uint8_t m_half_width;
    uint8_t m_location;
    uint8_t m_top;
    uint8_t m_bottom;
    enum direction m_direction;
};

#endif