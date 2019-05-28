#ifndef _HX711RAAT_H_
#define _HX711RAAT_H_

class HX711RAAT : public DeviceBase
{
public:
    HX711RAAT(uint8_t dout_pin, uint8_t sck_pin);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
private:

	int handle_set_command(char const * const command, char * reply);
	word sendEthernet(char * to_send);

    uint8_t m_dout_pin;
    uint8_t m_sck_pin;
    
};

#endif
