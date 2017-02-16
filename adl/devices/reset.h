#ifndef _RESET_H_
#define _RESET_H_

class Reset : public DeviceBase
{
public:
	Reset();
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);

};

#endif