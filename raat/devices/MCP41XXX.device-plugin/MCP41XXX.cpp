#include <SPI.h>
#include "raat.hpp"

#include "MCP41XXX.hpp"

MCP41XXX::MCP41XXX(uint8_t cs_pin) : m_cs_pin(cs_pin)
{

}

void MCP41XXX::reset() {}
void MCP41XXX::tick() {}

void MCP41XXX::setup()
{
    SPI.begin();
    pinMode(m_cs_pin, OUTPUT);
    digitalWrite(m_cs_pin, HIGH);
}

void MCP41XXX::set_wiper(uint8_t position)
{
    digitalWrite(m_cs_pin, LOW);

    SPI.transfer(0b00010001);
    SPI.transfer(position);

    digitalWrite(m_cs_pin, HIGH);
   
}

uint8_t MCP41XXX::handle_set_wiper_command(char const * const command, char * reply)
{
    int32_t resistance;
    bool ok = false;

    if ((ok = raat_parse_single_numeric(&command[2], resistance, NULL)))
    {
        this->set_wiper(resistance);
        strcpy(reply, "OK");
    }

    if (!ok)
    {
        strcpy(reply, "?");
    }

    return strlen(reply);
}

uint16_t MCP41XXX::command_handler(char const * const command, char * reply)
{
    bool ok = true;
    if (strncmp(command, "SW", 2) == 0)
    {
        this->handle_set_wiper_command(command, reply);
    }
    else
    {
        strcpy(reply, "CMD?");
    }
    return strlen(reply);
}
