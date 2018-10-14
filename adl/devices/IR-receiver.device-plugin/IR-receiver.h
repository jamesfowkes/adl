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
	
	bool get_code(unsigned long& code);

private:

	uint8_t handle_query_command(char const * const command, char * reply);
		
	decode_results m_results;
	IRrecv m_irrecv;
};

#endif