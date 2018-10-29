#ifndef _PARAMETER_H_
#define _PARAMETER_H_

class ParameterBase
{
public:

	ParameterBase(bool use_eeprom, size_t size)
	{
		m_use_eeprom = use_eeprom;
		if (use_eeprom)
		{
			m_eeprom_location.size = size;
			adl_nv_alloc(m_eeprom_location);
		}
	}

    virtual void reset() = 0;
    virtual void setup() = 0;
    virtual int command_handler(char const * const command, char * reply) = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    void tick() {};

protected:
	bool m_use_eeprom;
	ADL_NV_LOCATION m_eeprom_location;
};

#ifdef UNITTEST
class TestParam : public ParameterBase
{
public:
	TestParam();
    void reset() {};
    void setup() {};
    int command_handler(char const * const command, char * reply);

    void save() { adl_nv_save(&m_data, m_eeprom_location); }
    void load() { adl_nv_load(&m_data, m_eeprom_location); }

	int32_t m_data;
	char m_last_command[128];
};
#endif

#endif
