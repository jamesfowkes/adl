#ifndef _STRING_PARAM_H_
#define _STRING_PARAM_H_

class StringParam : public ParameterBase
{
public:
    StringParam(char const * const p_reset_value, uint16_t max_length, bool use_eeprom);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);

    void get(char * const dst);
    bool set(char const * const src);

    void save();
    void load();

private:
    char * m_pValue;
    char * m_pResetValue;
    
    uint16_t m_length;
};

#endif