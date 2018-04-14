#ifndef _DEBOUNCED_INPUT_
#define _DEBOUNCED_INPUT_

class DebouncedInput : public DeviceBase
{
public:
	DebouncedInput(int pin, uint16_t debounce_time, bool pullup);
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);
	void tick();
	bool check_high_and_clear();
	bool check_low_and_clear();
	bool state();
	
private:
	int m_pin;
	bool m_pullup;
	uint16_t m_count_max;
	uint16_t m_count;
	bool m_just_high;
	bool m_just_low;
	bool m_state;
};

#endif
