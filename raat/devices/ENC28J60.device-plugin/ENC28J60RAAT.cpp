#include <EtherCard.h>

#include "raat.hpp"

#include "ENC28J60RAAT.hpp"

byte Ethernet::buffer[ENC28J60_BUFFER_SIZE];

static const char IP_FORMAT[] PROGRAM_MEMORY = "IP: %d.%d.%d.%d";
static const char MAC_FORMAT[] PROGRAM_MEMORY = "MAC: %02x:%02x:%02x:%02x:%02x:%02x";
static const char GATEWAY_FORMAT[] PROGRAM_MEMORY = "Gateway: %d.%d.%d.%d";

static const char INIT_STRING[] PROGRAM_MEMORY = "Initialising ENC28J60...";
static const char CONFIG_STRING[] PROGRAM_MEMORY = "Configuring network params...";
static const char FAIL_STRING[] PROGRAM_MEMORY = "Failed to access ENC28J60";

ENC28J60RAAT::ENC28J60RAAT(uint8_t cs_pin) :
    m_cs_pin(cs_pin)
{

    m_mac_eeprom_location.size = 6;
    m_ip_eeprom_location.size = 4;
    m_gateway_eeprom_location.size = 4;
    raat_nv_alloc(m_mac_eeprom_location);
    raat_nv_alloc(m_ip_eeprom_location);
    raat_nv_alloc(m_gateway_eeprom_location);
}

void ENC28J60RAAT::tick()
{
    word len = ether.packetReceive();
    word pos = ether.packetLoop(len);

    if (pos)
    {
        ethernet_packet_handler((char *) Ethernet::buffer + pos);
        ether.httpServerReply(sendEthernet(ethernet_response_provider()));
    }
}

void ENC28J60RAAT::reset()
{

}

void ENC28J60RAAT::print_settings()
{
    raat_logln_P(LOG_RAAT, IP_FORMAT,
        m_ip_address[0], m_ip_address[1], m_ip_address[2], m_ip_address[3]);
    raat_logln_P(LOG_RAAT, MAC_FORMAT,
        m_mac_address[0], m_mac_address[1], m_mac_address[2], m_mac_address[3], m_mac_address[4], m_mac_address[5]);
    raat_logln_P(LOG_RAAT, GATEWAY_FORMAT,
        m_gateway[0], m_gateway[1], m_gateway[2], m_gateway[3]);
}

void ENC28J60RAAT::setup()
{
    this->reset();

    raat_nv_load(m_mac_address, m_mac_eeprom_location);
    raat_nv_load(m_ip_address, m_ip_eeprom_location);
    raat_nv_load(m_gateway, m_gateway_eeprom_location);

    this->print_settings();

    raat_logln_P(LOG_RAAT, INIT_STRING);
    if (ether.begin(ENC28J60_BUFFER_SIZE, m_mac_address, m_cs_pin) == 0) 
    {
        raat_logln_P(LOG_RAAT, FAIL_STRING);
    }

    raat_logln_P(LOG_RAAT, CONFIG_STRING);
    ether.staticSetup(m_ip_address, m_gateway);
}

int ENC28J60RAAT::handle_set_command(char const * const command, char * reply)
{
    enum 
    {
        BAD_COMMAND,
        BAD_VALUE,
        OK
    } result = BAD_COMMAND;

    int n = 0;
    unsigned int local_scan_buffer[6] = {0};
    uint8_t reply_length = 0;

    if (strncmp(command, "MAC", 3) == 0)
    {
        n = sscanf(command+3, "%02x:%02x:%02x:%02x:%02x:%02x",
            &local_scan_buffer[0], &local_scan_buffer[1], &local_scan_buffer[2],
            &local_scan_buffer[3], &local_scan_buffer[4], &local_scan_buffer[5]
        );
        result = (n == 6) ? OK : BAD_VALUE;
        if (result == OK)
        {
            for (uint8_t i=0; i<6; i++) { m_mac_address[i] = local_scan_buffer[i]; }
            raat_nv_save(m_mac_address, m_mac_eeprom_location);
        }
    }
    else if (strncmp(command, "IP", 2) == 0)
    {
        n = sscanf(command+2, "%d.%d.%d.%d",
            &local_scan_buffer[0], &local_scan_buffer[1], &local_scan_buffer[2], &local_scan_buffer[3]
        );
        result = (n == 4) ? OK : BAD_VALUE;
        if (result == OK)
        {
            for (uint8_t i=0; i<4; i++) { m_ip_address[i] = local_scan_buffer[i]; }
            raat_nv_save(m_ip_address, m_ip_eeprom_location);
        }
    }
    else if (strncmp(command, "GWAY", 4) == 0)
    {
        n = sscanf(command+4, "%d.%d.%d.%d",
            &local_scan_buffer[0], &local_scan_buffer[1], &local_scan_buffer[2], &local_scan_buffer[3]
        );
        result = (n == 4) ? OK : BAD_VALUE;
        if (result == OK)
        {
            for (uint8_t i=0; i<4; i++) { m_gateway[i] = local_scan_buffer[i]; }
            raat_nv_save(m_gateway, m_gateway_eeprom_location);
        }
    }

    switch(result)
    {
    case OK:
        strncpy(reply, "OK", 2);
        reply_length = 2;
        break;
    case BAD_VALUE:
        reply_length = sprintf(reply, "VAL (n=%d)?", n);
        break;
    case BAD_COMMAND:
        strncpy(reply, "CMD?", 4);
        reply_length = 4;
        break;
    }


    return reply_length;
}

int ENC28J60RAAT::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;

    switch(command[0])
    {
    case 'S':
        reply_length = this->handle_set_command(&command[1], reply);
        break;
    case '?':
        this->print_settings();
        strncpy(reply, "OK", 2);
        reply_length = 2;
        break;
    }
    return reply_length;
}

word ENC28J60RAAT::sendEthernet(char * to_send)
{
    m_bfill = ether.tcpOffset();
    m_bfill.emit_raw(to_send, strlen(to_send));
    return m_bfill.position();
}
