#ifndef _ANALOG_OUTPUT_H_
#define _ANALOG_OUTPUT_H_

class AnalogOutput : public DeviceBase
{
public:
	AnalogOutput(int pin, int limit_min=0, int limit_max=255);
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);
	
private:
	int m_pin;
	int m_limit_min;
	int m_limit_max;

};

#endif