#ifndef _RAAT_LED_FADER_H_
#define _RAAT_LED_FADER_H_

#include <stdint.h>

enum LEDFaderType
{
    LEDFaderType_Linear,
    LEDFaderType_Exponential,
    LEDFaderType_Custom
};

template<class INT_TYPE>
using setter_fn = void (*)(INT_TYPE *pLEDS, const uint8_t nleds, const INT_TYPE * m_p_max_values, const uint16_t stepnumber, const uint16_t max_stepnumber);

template <class INT_TYPE>
static void linearvalue_getter(INT_TYPE *pLEDS, const uint8_t nleds, const INT_TYPE * m_p_max_values, const uint16_t stepnumber, const uint16_t max_stepnumber)
{
    for (uint8_t i = 0; i < nleds; i++)
    {
        pLEDS[i*3+0] = (stepnumber * m_p_max_values[0])/max_stepnumber;
        pLEDS[i*3+1] = (stepnumber * m_p_max_values[1])/max_stepnumber;
        pLEDS[i*3+2] = (stepnumber * m_p_max_values[2])/max_stepnumber;
    }
}

template <class INT_TYPE>
static void expvalue_getter(INT_TYPE *pLEDS, const uint8_t nleds, const INT_TYPE * m_p_max_values, const uint16_t stepnumber, const uint16_t max_stepnumber)
{
    (void)pLEDS;
    (void)nleds;
    (void)m_p_max_values;
    (void)stepnumber;
    (void)max_stepnumber;
}


template <class INT_TYPE>
class LEDFader
{
public:
    LEDFader(INT_TYPE * dst, uint8_t n_leds, setter_fn<INT_TYPE>);
    LEDFader(INT_TYPE * dst, uint8_t n_leds, enum LEDFaderType faderType);

    void setup();
    void reset();
    void tick();

    void print();
    void print(INT_TYPE * pleds);
    void print(INT_TYPE * pleds, uint8_t min_index, uint8_t max_index);

    void start(bool direction_up, INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b, uint16_t number_of_steps);
    void start(bool direction_up, INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b, uint16_t number_of_steps, int8_t number_of_runs);

    bool update();

private:

    void set_next();
    
    INT_TYPE * m_p_leds;
    INT_TYPE * m_p_max_values;

    uint8_t m_n_leds;
    uint16_t m_current_step;
    uint16_t m_max_steps;
    int8_t m_runs;
    bool m_direction_up;

    enum LEDFaderType m_fader_type;

    setter_fn<INT_TYPE> m_pfn_value_getter;
};

template <class INT_TYPE>
LEDFader<INT_TYPE>::LEDFader(INT_TYPE * dst, uint8_t n_leds, setter_fn<INT_TYPE> pfn_value_getter) : 
    m_p_leds(dst), m_n_leds(n_leds), m_current_step(0), m_max_steps(0), m_runs(0), m_direction_up(true),
    m_fader_type(LEDFaderType_Custom), m_pfn_value_getter(pfn_value_getter)
{
}

template <class INT_TYPE>
LEDFader<INT_TYPE>::LEDFader(INT_TYPE * dst, uint8_t n_leds, enum LEDFaderType faderType) : 
    m_p_leds(dst), m_n_leds(n_leds), m_current_step(0), m_max_steps(0), m_runs(0), m_direction_up(true),
    m_fader_type(faderType), m_pfn_value_getter(NULL)
{
    m_p_max_values = (INT_TYPE*)malloc(n_leds * 3 * sizeof(INT_TYPE));
    switch(m_fader_type)
    {
    case LEDFaderType_Linear:
        m_pfn_value_getter = linearvalue_getter;
        break;
    case LEDFaderType_Exponential:
        m_pfn_value_getter = expvalue_getter;
        break;
    default:
    case LEDFaderType_Custom:
        break;
    }
}

template <class INT_TYPE>
void LEDFader<INT_TYPE>::start(bool direction_up, INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b, uint16_t number_of_steps)
{
    this->start(direction_up, max_r, max_g, max_b, number_of_steps, CONTINUOUS_EFFECT);
}

template <class INT_TYPE>
void LEDFader<INT_TYPE>::start(bool direction_up, INT_TYPE max_r, INT_TYPE max_g, INT_TYPE max_b,
    uint16_t number_of_steps, int8_t number_of_runs)
{
    m_direction_up = direction_up;
    m_runs = number_of_runs;
    m_current_step = 0;
    m_max_steps = number_of_steps;
    m_p_max_values[0] = max_r;
    m_p_max_values[1] = max_g;
    m_p_max_values[2] = max_b;
    if (direction_up)
    {
        memset(m_p_leds, 0, m_n_leds * sizeof(INT_TYPE) * 3);
    }
    else
    {
        for (uint8_t i = 0; i < m_n_leds; i++)
        {
            m_p_leds[i*3+0] = m_p_max_values[0];
            m_p_leds[i*3+1] = m_p_max_values[1];
            m_p_leds[i*3+2] = m_p_max_values[2];
        }
    }
}

template <class INT_TYPE>
bool LEDFader<INT_TYPE>:: update()
{
    if (m_current_step < m_max_steps)
    {
        m_current_step++;
        uint8_t actual_step = m_direction_up ? m_current_step : m_max_steps - m_current_step;
        m_pfn_value_getter(m_p_leds, m_n_leds, m_p_max_values, actual_step, m_max_steps);
    }
    return m_current_step < m_max_steps;
}

#endif
