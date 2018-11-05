#include <stdint.h>
#include <stdlib.h>

#include "adl.h"
#include "adl-util-limited-range-int.h"

LimitedRangeInt::LimitedRangeInt(int32_t init_value, int32_t min_val, int32_t max_val, bool clip_on_out_of_range):
m_min(min_val), m_max(max_val)
{
    m_clip_on_out_of_range = clip_on_out_of_range;
    m_value = 0;
    (void)this->set(init_value);
}

bool LimitedRangeInt::check(int32_t to_check)
{
    return (to_check <= m_max) && (to_check >= m_min);
}

bool LimitedRangeInt::set(int32_t to_set)
{
    bool in_range = this->check(to_set);

    if (in_range)
    {
        m_value = to_set;
    }
    else if (m_clip_on_out_of_range && (to_set > m_max))
    {
        m_value = m_max;
    }
    else if (m_clip_on_out_of_range && (to_set < m_min))
    {
        m_value = m_min;
    }
    return in_range;
}

int32_t LimitedRangeInt::value()
{
    return m_value;
}

int32_t LimitedRangeInt::operator=(const int32_t rhs)
{
    this->set(rhs);
    return this->m_value;
}

int32_t LimitedRangeInt::operator+(const int32_t other)
{
    this->add(other);
    return this->m_value;
}

int32_t LimitedRangeInt::operator++()
{
    this->add(1);
    return this->m_value;
}

int32_t LimitedRangeInt::operator++(int)
{
    operator++();
    return this->m_value;
}

int32_t LimitedRangeInt::operator+=(const int32_t rhs)
{
    this->add(rhs);
    return this->m_value;
}


int32_t LimitedRangeInt::operator-(const int32_t other)
{
    this->sub(other);
    return this->m_value;
}

int32_t LimitedRangeInt::operator--()
{
    this->sub(1);
    return this->m_value;
}

int32_t LimitedRangeInt::operator--(int)
{
    operator--();
    return this->m_value;
}

int32_t LimitedRangeInt::operator-=(const int32_t rhs)
{
    this->sub(rhs);
    return this->m_value;
}

void LimitedRangeInt::add(int32_t to_add)
{
    if (this->addition_will_overflow(to_add))
    {
        this->set(m_max);
    }
    else
    {
        this->set(m_value + to_add);
    }
}

void LimitedRangeInt::sub(int32_t to_sub)
{
    if (this->subtraction_will_underflow(to_sub))
    {
        this->set(m_min);
    }
    else
    {
        this->set(m_value - to_sub);
    }
}

bool LimitedRangeInt::addition_will_overflow(int32_t to_add)
{
    int32_t new_value = m_value + to_add;
    return new_value < m_value;
}

bool LimitedRangeInt::subtraction_will_underflow(int32_t to_sub)
{
    int32_t new_value = m_value - to_sub;
    return new_value > m_value;
}
