#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

class DigitalOutput : public DeviceBase
{
public:
	DigitalOutput(int pin);
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);
	
private:
	int m_pin;
};

#endif