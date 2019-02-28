#ifndef _RFID_RC522_H_
#define _RFID_RC522_H_

class RFID_RC522 : public DeviceBase
{
public:
	RFID_RC522(int ss_pin, int rst_pin);
	void setup();
	void reset();
	void tick();
	uint8_t get(char * buffer);
	
	int command_handler(char const * const command, char * reply);

private:
	MFRC522 * m_mfrc522;
};

#endif
