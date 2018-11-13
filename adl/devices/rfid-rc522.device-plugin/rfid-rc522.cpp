#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

#include "adl.h"

#include "rfid-rc522.h"

static char nibble_to_hex(uint8_t b)
{
	return (b < 10) ? ('0' + b) : ('A' + (b-10));
}

static void byte_to_hex(char * buffer, uint8_t b)
{
	uint8_t upper = (b & 0xF0) >> 4;
	uint8_t lower = (b & 0x0F);

	buffer[0] = nibble_to_hex(upper);
	buffer[1] = nibble_to_hex(lower);
}

RFID_RC522::RFID_RC522(int ss_pin, int rst_pin)
{
	m_mfrc522 = new MFRC522(ss_pin, rst_pin);
}

void RFID_RC522::reset() {}

void RFID_RC522::setup()
{
	SPI.begin();
	m_mfrc522->PCD_Init();
}

int RFID_RC522::command_handler(char const * const command, char * reply)
{
	int reply_len = 0;

	if (command[0] == 'R')
	{
		if (m_mfrc522->PICC_IsNewCardPresent() && m_mfrc522->PICC_ReadCardSerial())
		{
			for (int i = 0; i < m_mfrc522->uid.size; i++)
			{
				byte_to_hex(&reply[i*2], m_mfrc522->uid.uidByte[i]);
			}
			reply[m_mfrc522->uid.size*2] = '\0';
			//reply[m_mfrc522->uid.size*2] = m_mfrc522->uid.size + '0';
			reply_len = m_mfrc522->uid.size*2;
		}
		else
		{
			strcpy(reply, "NOCARD");
			reply_len = 6;
		}
	}
	else
	{
		strcpy(reply, "CMD?");
		reply_len = 4;
	}

	return reply_len;
}

void RFID_RC522::tick()
{

}
