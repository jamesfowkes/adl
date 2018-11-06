#ifndef _INTEGER_PARAM_H_
#define _INTEGER_PARAM_H_

#include "adl-util-limited-range-int.h"

class IntegerParam : public ParameterBase
{
public:
    IntegerParam(int32_t reset_value, int32_t min_limit, int32_t max_limit,
    	bool clip_on_out_of_range, bool use_eeprom);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    
    bool set(int32_t setting);
    int32_t get();

    void save();
    void load();
    
private:
    int32_t m_reset_value;
    LimitedRangeInt m_value;
};

#endif