#ifndef _ENC28J60RAAT_H_
#define _ENC28J60RAAT_H_

class ENC28J60RAAT : public DeviceBase
{
public:
    ENC28J60RAAT(uint8_t cs_pin);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
    void print_settings();

private:

	int handle_set_command(char const * const command, char * reply);
	word sendEthernet(char * to_send);

	uint8_t m_mac_address[6];
	uint8_t m_ip_address[4];
	uint8_t m_gateway[4];

    uint8_t m_cs_pin;
    
    RAAT_NV_LOCATION m_mac_eeprom_location;
    RAAT_NV_LOCATION m_ip_eeprom_location;
    RAAT_NV_LOCATION m_gateway_eeprom_location;

    BufferFiller m_bfill;
};

// Expected to be implemented by userspace code
void ethernet_packet_handler(char * req);
char * ethernet_response_provider();

#endif
