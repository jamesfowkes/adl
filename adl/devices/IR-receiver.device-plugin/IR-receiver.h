#ifndef _IR_RECEIVER_H_
#define _IR_RECEIVER_H_

class IR_Receiver : public DeviceBase
{
public:
	IR_Receiver(uint8_t pin);
	void setup();
	void reset();
	void tick();
	int command_handler(char const * const command, char * reply);
	
	void read();

private:
	IRrecv m_irrecv;
};

#endif