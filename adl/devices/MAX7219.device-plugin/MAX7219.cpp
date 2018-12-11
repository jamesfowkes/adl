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

MAX7219::MAX7219(uint8_t cs, uint8_t din, uint8_t dclk, uint8_t device_count) :
  m_CS(cs), m_DATA(din), m_DCLK(dclk), m_device_count(device_count)
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
    (void)command; (void)reply;
    int reply_length = 0;
    return reply_length;
}

void MAX7219::ClockOut(uint8_t reg, uint8_t data)
{
    digitalWrite(m_DCLK, LOW);
    shiftOut(m_DATA, m_DCLK, MSBFIRST, reg);
    digitalWrite(m_DCLK, LOW);
    shiftOut(m_DATA, m_DCLK, MSBFIRST, data);
    digitalWrite(m_CS, LOW);
    
}
void MAX7219::writeRegister(uint8_t reg, uint8_t data)
{
    digitalWrite(m_CS, LOW);
    this->ClockOut(reg, data);
    digitalWrite(m_CS, HIGH);
}

void MAX7219::Set(uint8_t * data)
{
    uint8_t max_data_index;

    if (data)
    {
        max_data_index  = (m_device_count*8)-1;
        
        for (uint8_t digit=0; digit < 8; digit++)
        {
            digitalWrite(m_CS, LOW);
            for (uint8_t dev=0; dev<m_device_count; dev++)
            {
                uint8_t index = max_data_index - ((dev*8)+digit);
                this->ClockOut(eRegister_D0 + digit, data[index]);
            }
            digitalWrite(m_CS, HIGH);
        }
    }
}

void MAX7219::ClearAll()
{
    uint8_t max_data_index;
    for (uint8_t digit=0; digit < 8; digit++)
    {
        max_data_index  = (m_device_count*8)-1;
        
        for (uint8_t digit=0; digit < 8; digit++)
        {
            digitalWrite(m_CS, LOW);
            for (uint8_t dev=0; dev<m_device_count; dev++)
            {
                uint8_t index = max_data_index - ((dev*8)+digit);
                this->ClockOut(eRegister_D0 + digit, 0x00);
            }
            digitalWrite(m_CS, HIGH);
        }
    }
}

void MAX7219::SetDecode(eDecodeMode eMode)
{
    writeRegister(eRegister_DecodeMode, (uint8_t)eMode);
}

void MAX7219::SetIntensity(uint8_t intensity)
{
    if (intensity > 15)
    {
        intensity = 15;
    }
    writeRegister(eRegister_Intensity, intensity);
}

void MAX7219::SetScanLimit(uint8_t limit)
{
    if (limit > 7)
    {
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
