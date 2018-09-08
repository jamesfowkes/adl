#ifndef _LIMITED_RANGE_INT_H_
#define _LIMITED_RANGE_INT_H_

class LimitedRangeInt
{
public:
    LimitedRangeInt(int32_t init_value, int32_t min_val, int32_t max_val, bool clip_on_out_of_range);
    bool set(int32_t to_set);
    bool check(int32_t to_check);
    
    int32_t value();

    int32_t operator=(const int32_t rhs);

    int32_t operator+(const int32_t other);
    int32_t operator++();
    int32_t operator++(int);
    int32_t operator+=(const int32_t rhs);

    int32_t operator-(const int32_t other);
    int32_t operator--();
    int32_t operator--(int);
    int32_t operator-=(const int32_t rhs);

private:

    bool addition_will_overflow(int32_t to_add);
    void add(int32_t to_add);
    bool subtraction_will_underflow(int32_t to_sub);
    void sub(int32_t to_sub);
    
    int32_t m_min;
    int32_t m_max;
    int32_t m_value;
    bool m_clip_on_out_of_range;
};

#endif