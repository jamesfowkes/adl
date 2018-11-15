#ifndef _ADL_UTIL_DEBOUNCER_H_
#define _ADL_UTIL_DEBOUNCER_H_

class DebounceReader
{
public:
	virtual bool read() = 0;
};

typedef bool (*debounce_read_fn)(void);

class ADLDebouncer
{
public:
    ADLDebouncer(DebounceReader& reader, uint16_t debounce_ticks);
    ADLDebouncer(debounce_read_fn readfn, uint16_t debounce_ticks);
    void setup();
    void reset();
    void tick();
    bool check_high_and_clear();
    bool check_low_and_clear();
    bool state();
    uint16_t count();

private:
    uint16_t m_count_max;
    uint16_t m_count;
    bool m_just_high;
    bool m_just_low;
    bool m_state;
    DebounceReader * mp_reader;
    debounce_read_fn mp_read_fn;
};
#endif