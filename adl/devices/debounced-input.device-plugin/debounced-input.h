#ifndef _DEBOUNCED_INPUT_
#define _DEBOUNCED_INPUT_

#include "adl-debouncer.h"

class DebouncedInput : public DeviceBase, public DebounceReader
{
public:
    DebouncedInput(int pin, uint16_t debounce_time, bool pullup, bool invert);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    void tick();
    bool check_high_and_clear();
    bool check_low_and_clear();
    bool state();
    bool read();
    
private:
    int m_pin;
    bool m_pullup;
    bool m_invert;
    ADLDebouncer m_debouncer;
};

#endif
