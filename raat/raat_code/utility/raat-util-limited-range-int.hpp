#ifndef _LIMITED_RANGE_INT_H_
#define _LIMITED_RANGE_INT_H_

template <class INT_TYPE>
class LimitedRangeInt
{
public:
    LimitedRangeInt(INT_TYPE init_value, INT_TYPE min_val, INT_TYPE max_val, bool clip_on_out_of_range);
    bool set(INT_TYPE to_set);
    bool check(INT_TYPE to_check);
    
    INT_TYPE value();

    INT_TYPE operator=(const INT_TYPE rhs);

    INT_TYPE operator+(const INT_TYPE other);
    INT_TYPE operator++();
    INT_TYPE operator++(int);
    INT_TYPE operator+=(const INT_TYPE rhs);

    INT_TYPE operator-(const INT_TYPE other);
    INT_TYPE operator--();
    INT_TYPE operator--(int);
    INT_TYPE operator-=(const INT_TYPE rhs);

private:

    bool addition_will_overflow(INT_TYPE to_add);
    void add(INT_TYPE to_add);
    bool subtraction_will_underflow(INT_TYPE to_sub);
    void sub(INT_TYPE to_sub);
    
    INT_TYPE m_min;
    INT_TYPE m_max;
    INT_TYPE m_value;
    bool m_clip_on_out_of_range;
};

template <class INT_TYPE>
LimitedRangeInt<INT_TYPE>::LimitedRangeInt(INT_TYPE init_value, INT_TYPE min_val, INT_TYPE max_val, bool clip_on_out_of_range):
m_min(min_val), m_max(max_val)
{
    m_clip_on_out_of_range = clip_on_out_of_range;
    m_value = 0;
    (void)this->set(init_value);
}

template <class INT_TYPE>
bool LimitedRangeInt<INT_TYPE>::check(INT_TYPE to_check)
{
    return (to_check <= m_max) && (to_check >= m_min);
}

template <class INT_TYPE>
bool LimitedRangeInt<INT_TYPE>::set(INT_TYPE to_set)
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

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::value()
{
    return m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator=(const INT_TYPE rhs)
{
    this->set(rhs);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator+(const INT_TYPE other)
{
    this->add(other);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator++()
{
    this->add(1);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator++(int)
{
    operator++();
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator+=(const INT_TYPE rhs)
{
    this->add(rhs);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator-(const INT_TYPE other)
{
    this->sub(other);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator--()
{
    this->sub(1);
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator--(int)
{
    operator--();
    return this->m_value;
}

template <class INT_TYPE>
INT_TYPE LimitedRangeInt<INT_TYPE>::operator-=(const INT_TYPE rhs)
{
    this->sub(rhs);
    return this->m_value;
}

template <class INT_TYPE>
void LimitedRangeInt<INT_TYPE>::add(INT_TYPE to_add)
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

template <class INT_TYPE>
void LimitedRangeInt<INT_TYPE>::sub(INT_TYPE to_sub)
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

template <class INT_TYPE>
bool LimitedRangeInt<INT_TYPE>::addition_will_overflow(INT_TYPE to_add)
{
    INT_TYPE new_value = m_value + to_add;
    return new_value < m_value;
}

template <class INT_TYPE>
bool LimitedRangeInt<INT_TYPE>::subtraction_will_underflow(INT_TYPE to_sub)
{
    INT_TYPE new_value = m_value - to_sub;
    return new_value > m_value;
}

#endif