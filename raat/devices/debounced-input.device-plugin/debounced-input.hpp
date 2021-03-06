#ifndef _DEBOUNCED_INPUT_
#define _DEBOUNCED_INPUT_

#include "raat-debouncer.hpp"

class DebouncedInput : public DeviceBase, public DebounceReader
{
public:
    DebouncedInput(uint8_t pin, uint16_t debounce_time, bool pullup, bool invert);
    void setup();
    void reset();
    uint16_t command_handler(char const * const command, char * reply);
    void tick();
    bool check_high_and_clear();
    bool check_low_and_clear();
    bool state();
    bool read();
    uint8_t pin();
private:
    uint8_t m_pin;
    bool m_pullup;
    bool m_invert;
    RAATDebouncer m_debouncer;
};

#endif
