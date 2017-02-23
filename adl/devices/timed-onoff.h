#ifndef _TIMED_ONOFF_
#define _TIMED_ONOFF_

class TimedOnOff : public DeviceBase
{
public:
	TimedOnOff(int pin, unsigned long ontime, unsigned long offtime);
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);
	void tick();
	
private:
	int m_pin;
	bool m_state;
	unsigned long m_ontime;
	unsigned long m_offtime;
	unsigned long m_last_time;
	unsigned long m_interval;

};

#endif