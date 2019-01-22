#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

#include "raat.h"

#include "rfid-rc522.h"

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

uint8_t RFID_RC522::get(char * buffer)
{
	uint8_t length = 0;

	if (buffer && m_mfrc522->PICC_IsNewCardPresent() && m_mfrc522->PICC_ReadCardSerial())
	{
		for (int i = 0; i < m_mfrc522->uid.size; i++)
		{
			byte_to_hex(&buffer[i*2], m_mfrc522->uid.uidByte[i]);
		}
		buffer[m_mfrc522->uid.size*2] = '\0';
		length = m_mfrc522->uid.size*2;
	}	
	return length;
}

int RFID_RC522::command_handler(char const * const command, char * reply)
{
	int reply_len = 0;

	if (command[0] == '?')
	{
		reply_len = this->get(reply);
		if(reply_len == 0)
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
