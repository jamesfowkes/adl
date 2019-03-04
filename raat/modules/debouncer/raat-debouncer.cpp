#include "raat.hpp"

#include "raat-debouncer.hpp"

RAATDebouncer::RAATDebouncer(DebounceReader& reader, uint16_t debounce_ticks) : 
    m_count_max(debounce_ticks),
    m_count(0),
    m_just_high(false),
    m_just_low(false),
    m_state(false),
    mp_reader(&reader),
    mp_read_fn(NULL)
{

}

RAATDebouncer::RAATDebouncer(debounce_read_fn readfn, uint16_t debounce_ticks) :
    m_count_max(debounce_ticks),
    m_count(0),
    m_just_high(false),
    m_just_low(false),
    m_state(false),
    mp_reader(NULL),
    mp_read_fn(readfn)
{

}

void RAATDebouncer::reset()
{
    m_state = false;
    m_count = 0;
}

void RAATDebouncer::setup()
{
    this->reset();
}

bool RAATDebouncer::check_high_and_clear()
{
    bool value = m_just_high;
    m_just_high = false;
    return value;
}

bool RAATDebouncer::check_low_and_clear()
{
    bool value = m_just_low;
    m_just_low = false;
    return value;
}

bool RAATDebouncer::state()
{
    return m_state;
}

void RAATDebouncer::tick()
{
    bool high;

    if (this->mp_reader)
    {
        high= this->mp_reader->read();
    }
    else if (this->mp_read_fn)
    {
        high = this->mp_read_fn();
    }
    else
    {
        return; 
    }

    if (high)
    {
        m_count = (m_count < m_count_max) ? m_count+1 : m_count;
        
        if (!m_state && (m_count == m_count_max))
        {
            m_just_high = true;
            m_just_low = false;
        }

        if (m_count == m_count_max) { m_state = true; }
    }
    else
    {
        m_count = (m_count > 0) ? m_count-1 : m_count;
        
        if (m_state && (m_count == 0))
        {
            m_just_low = true;
            m_just_high = false;
        }

        if (m_count == 0) { m_state = false; }
    }
}

uint16_t RAATDebouncer::count()
{
    return m_count;
}
