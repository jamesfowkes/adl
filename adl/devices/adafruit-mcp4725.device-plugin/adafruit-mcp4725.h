#ifndef _ADAFRUIT_MCP4725_ADL_H_
#define _ADAFRUIT_MCP4725_ADL_H_

class Adafruit_MCP4725ADL : public DeviceBase
{
public:
	Adafruit_MCP4725ADL(ADC_SUBTYPE ads_subtype, float multiplier);
	void setup();
	void reset();
	void tick();
	int command_handler(char const * const command, char * reply);
	
private:
	Adafruit_MCP4725 m_dac;
	uint8_t handle_query_command(char const * const command, char * reply);
	uint8_t handle_setting_command(char const * const command, char * reply);
};

#endif