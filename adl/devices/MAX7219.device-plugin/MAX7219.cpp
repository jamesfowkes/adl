#include "adl.h"

#include "MAX7219.h"

typedef enum _eRegisters
{
  eRegister_Noop,
  eRegister_D0,
  eRegister_D1,
  eRegister_D2,
  eRegister_D3,
  eRegister_D4,
  eRegister_D5,
  eRegister_D6,
  eRegister_D7,
  eRegister_DecodeMode,
  eRegister_Intensity,
  eRegister_ScanLimit,
  eRegister_Shutdown,
  eRegister_Test = 0x0F,
} eRegisters;

/*
 * Class Private Functions
 */

/*
 * Class Public Functions
 */

MAX7219::MAX7219(uint8_t cs, uint8_t din, uint8_t dclk) : m_CS(cs), m_DATA(din), m_DCLK(dclk)
{
  pinMode(m_CS, OUTPUT);
  pinMode(m_DATA, OUTPUT);
  pinMode(m_DCLK, OUTPUT);
  this->ClearAll();
}

void MAX7219::reset()
{
    
}

void MAX7219::tick()
{

}

void MAX7219::setup()
{
    this->reset();
}

int MAX7219::command_handler(char const * const command, char * reply)
{
    (void)command;
    int reply_length = 0;
    return reply_length;
}


void MAX7219::writeRegister(uint8_t reg, uint8_t data)
{
  digitalWrite(m_CS, LOW);
  digitalWrite(m_DCLK, LOW);
  shiftOut(m_DATA, m_DCLK, MSBFIRST, reg);
  digitalWrite(m_DCLK, LOW);
  shiftOut(m_DATA, m_DCLK, MSBFIRST, data);
  digitalWrite(m_CS, LOW);
  digitalWrite(m_CS, HIGH);
}

void MAX7219::SetOutputs(uint8_t digit, uint8_t data)
{
  if (digit < 8)
  {
    writeRegister(eRegister_D0 + digit, data);
  }
}

void MAX7219::ClearAll()
{
  for (uint8_t digit = 0; digit < 8; digit++)
  {
    writeRegister(eRegister_D0 + digit, 0x00);
  }
}

void MAX7219::SetDecode(eDecodeMode eMode)
{
  writeRegister(eRegister_DecodeMode, (uint8_t)eMode);
}

void MAX7219::SetIntensity(uint8_t intensity)
{
  if (intensity > 15) {
    intensity = 15;
  }
  writeRegister(eRegister_Intensity, intensity);
}

void MAX7219::SetScanLimit(uint8_t limit)
{
  if (limit > 7) {
    limit = 7;
  }
  writeRegister(eRegister_ScanLimit, limit);
}

void MAX7219::SetShutdown(bool shdn)
{
  writeRegister(eRegister_Shutdown, shdn ? 0x00 : 0x01);
}

void MAX7219::SetTest(bool test)
{
  writeRegister(eRegister_Test, test ? 0x01 : 0x00);
}
