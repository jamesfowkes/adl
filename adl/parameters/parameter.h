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
