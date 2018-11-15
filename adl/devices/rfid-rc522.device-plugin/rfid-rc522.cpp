#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

#include "adl.h"

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
