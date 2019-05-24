#ifndef _RAAT_LED_FADER_H_
#define _RAAT_LED_FADER_H_

#include <stdint.h>

enum LEDFaderType
{
    LEDFaderType_Linear,
    LEDFaderType_Exponential,
    LEDFaderType_Custom
};

template <class INT_TYPE>
class LEDFader
{
public:
    LEDFader(INT_TYPE * dst, uint8_t n_leds, void (*pfn_value_getter)(INT_TYPE linearvalue, INT_TYPE * pNewValue));
    LEDFader(INT_TYPE * dst, uint8_t n_leds, enum LEDFaderType faderType);

    void setup();
    void reset();
    void tick();

    void print();
    void print(INT_TYPE * pleds);
    void print(INT_TYPE * pleds, uint8_t min_index, uint8_t max_index);

    void start(INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b);
    void start(INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b, int8_t number_of_runs);

    bool update();

private:

    void set_next();
    
    INT_TYPE * mp_leds;
    INT_TYPE * mp_max_values;
    uint8_t m_n_leds;
    int8_t m_runs;

    enum LEDFaderType m_fader_type;

    void (*m_pfn_value_getter)(INT_TYPE linearvalue, INT_TYPE * pNewValue);
};

template <class INT_TYPE>
LEDFader<INT_TYPE>::LEDFader(INT_TYPE * dst, uint8_t n_leds, enum LEDFaderType faderType) : 
    mp_leds(dst), m_n_leds(n_leds), m_fader_type(faderType), m_pfn_value_getter(NULL)
{
    mp_max_values = (INT_TYPE*)malloc(n_leds * 3 * sizeof(INT_TYPE));
}

template <class INT_TYPE>
void LEDFader<INT_TYPE>::start(INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b)
{
    this->start(max_r, max_g, max_b, CONTINUOUS_EFFECT);
}

template <class INT_TYPE>
void LEDFader<INT_TYPE>::start(INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b, int8_t number_of_runs)
{
    m_runs = number_of_runs;
    mp_max_values[0] = max_r;
    mp_max_values[1] = max_g;
    mp_max_values[2] = max_b;
    memset(mp_leds, 0, m_n_leds * sizeof(INT_TYPE));
}

#endif
