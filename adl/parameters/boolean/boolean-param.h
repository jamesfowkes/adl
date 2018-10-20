#ifndef _BOOLEAN_PARAM_H_
#define _BOOLEAN_PARAM_H_

class BooleanParam : public ParameterBase
{
public:
    BooleanParam(bool reset_value, bool use_eeprom);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    
    bool set(bool setting);
    bool get();

    void save();
    void load();

private:
    bool m_reset_value;
    bool m_state;
};

#endif