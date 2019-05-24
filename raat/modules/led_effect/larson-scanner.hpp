#ifndef _RAAT_LARSON_SCANNER_H_
#define _RAAT_LARSON_SCANNER_H_

#include <stdint.h>

enum direction
{
	DIR_POS,
	DIR_NEG
};

template <class INT_TYPE>
class LarsonScanner
{
public:
    LarsonScanner(INT_TYPE * dst, uint8_t n_strip_leds, uint8_t n_larson_leds,
        void (*pfn_value_getter)(uint8_t index, INT_TYPE * pMultiplier, INT_TYPE * pDivisor)
    );

    void setup();
    void reset();
    void tick();

    void print();
    void print(INT_TYPE * pleds);
    void print(INT_TYPE * pleds, uint8_t min_index, uint8_t max_index);

    void start(INT_TYPE r, INT_TYPE g, INT_TYPE b);
    void start(INT_TYPE r, INT_TYPE g, INT_TYPE b, int8_t number_of_runs);

    bool update();
private:

	void set_next();
	void clear_last_pixel();
	INT_TYPE * mp_leds;
	INT_TYPE * mp_values;
    uint8_t m_n_strip_leds;
    uint8_t m_n_larson_leds;
    uint8_t m_half_width;
    uint8_t m_location;
    uint8_t m_top;
    uint8_t m_bottom;

    int8_t m_runs;

    enum direction m_direction;

    void (*m_pfn_value_getter)(uint8_t index, INT_TYPE * pMultiplier, INT_TYPE * pDivisor);
};

template <class INT_TYPE>
LarsonScanner<INT_TYPE>::LarsonScanner(INT_TYPE * dst, uint8_t n_strip_leds, uint8_t n_larson_leds,
    void (*pfn_value_getter)(uint8_t index, INT_TYPE * pMultiplier, INT_TYPE * pDivisor)) :
    mp_leds(dst), m_n_strip_leds(n_strip_leds), m_n_larson_leds(n_larson_leds),
    m_half_width(n_larson_leds/2), m_location(n_larson_leds/2), m_top(n_strip_leds - 1 - n_larson_leds/2),
    m_bottom(n_larson_leds/2),
    m_pfn_value_getter(pfn_value_getter)

{
    mp_values = (INT_TYPE*)malloc(n_larson_leds * 3 * sizeof(INT_TYPE));
}

#ifndef ARDUINO
template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::print()
{
    this->print(mp_leds);
}

template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::print(INT_TYPE * pleds)
{
    uint8_t min_index = m_location-m_half_width;
    if (min_index > 0)
    {
        min_index--;    
    }

    uint8_t max_index = m_location+m_half_width;

    if (max_index < m_n_strip_leds)
    {
        max_index++;    
    }

    this->print(pleds, min_index, max_index);
}

template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::print(INT_TYPE * pleds, uint8_t min_index, uint8_t max_index)
{
    std::cout << "LED values " << (int)min_index << "-" << (int)max_index << ":" << std::endl;
    for (uint8_t i=min_index; i<=max_index; i++)
    {
        std::cout << (int)pleds[i*3] << ","<< (int)pleds[i*3+1] << ","<< (int)pleds[i*3+2] << ",";
    }
    std::cout << std::endl;
}
#endif


template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::start(INT_TYPE r, INT_TYPE g, INT_TYPE b)
{
    this->start(r, g, b, CONTINUOUS_EFFECT);
}

template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::start(INT_TYPE r, INT_TYPE g, INT_TYPE b, int8_t number_of_runs)
{
    m_runs = number_of_runs;
    uint8_t middle_led_index = m_n_larson_leds/2;
    uint8_t divisor;
    uint8_t multiplier;

    for (uint8_t low_index=0; low_index<=middle_led_index; low_index++)
    {
        uint8_t high_index = m_n_larson_leds - low_index - 1;
        
        m_pfn_value_getter(low_index, &multiplier, &divisor);
        mp_values[low_index*3] = (r*multiplier)/divisor;
        mp_values[low_index*3+1] = (g*multiplier)/divisor;
        mp_values[low_index*3+2] = (b*multiplier)/divisor;

        mp_values[high_index*3] = (r*multiplier)/divisor;
        mp_values[high_index*3+1] = (g*multiplier)/divisor;
        mp_values[high_index*3+2] = (b*multiplier)/divisor;
    }
    m_direction = DIR_POS;

    INT_TYPE * pDst = &mp_leds[(m_location - m_half_width)*3];
    memcpy(pDst, mp_values, m_n_larson_leds*3);
}

template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::clear_last_pixel()
{
    uint8_t idx = 0;
    if (m_direction == DIR_POS)
    {
        idx = m_location-m_half_width;
    }
    else
    {
        idx = m_location+m_half_width;      
    }
    mp_leds[idx*3] = 0;
    mp_leds[idx*3+1] = 0;
    mp_leds[idx*3+2] = 0;
}

template <class INT_TYPE>
void LarsonScanner<INT_TYPE>::set_next()
{
    if (m_direction == DIR_POS)
    {
        if (m_location < m_top)
        {
            m_location++;
        }

        if (m_location == m_top)
        {
            m_direction = DIR_NEG;
        }
    }
    else
    {
        if (m_location > m_bottom)
        {
            m_location--;
        }

        if (m_location == m_bottom)
        {
            m_direction = DIR_POS;
        }
    }
}

template <class INT_TYPE>
bool LarsonScanner<INT_TYPE>::update()
{
    bool continue_scan = true;
    this->clear_last_pixel();
    this->set_next();

    if (m_runs > 0)
    {
        if (m_location == m_bottom)
        {
            m_runs--;
            continue_scan = m_runs > 0;
        }
    }

    if (continue_scan)
    {
        INT_TYPE * pDst = &mp_leds[(m_location - m_half_width)*3];
        memcpy(pDst, mp_values, m_n_larson_leds*3);
    }
    else
    {
        memset(mp_leds, 0, m_n_strip_leds*3);
    }

    return continue_scan;
}


#endif
