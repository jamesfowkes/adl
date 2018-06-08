#ifndef _ADL_KEYPAD_H_
#define _ADL_KEYPAD_H_

class ADLKeypad : public DeviceBase
{
public:
	ADLKeypad(Keypad& keypad);
	void setup();
	void reset();
	void tick();
	
	int command_handler(char const * const command, char * reply);

private:
	Keypad * m_pkeypad;
};

#endif
