#include "raat.hpp"

#include "MAX7219.hpp"

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
  mp_data = (uint8_t*)malloc(m_device_count * 8);
  this->clear_all();
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

uint16_t MAX7219::command_handler(char const * const command, char * reply)
{
    (void)command; (void)reply;
    int reply_length = 0;
    return reply_length;
}

void MAX7219::set(uint8_t device, uint8_t digit, uint8_t data)
{
    if (device >= m_device_count) { return; }
    if (digit >= 8) { return; }
    if (!mp_data) { return; }

    uint8_t index = (digit * m_device_count) + device;

    mp_data[index] = data;
}

uint8_t MAX7219::get(uint8_t device, uint8_t digit)
{
    if (device >= m_device_count) { return 0; }
    if (digit >= 8) { return 0; }
    if (!mp_data) { return 0; }

    uint8_t index = (digit * m_device_count) + device;
    return mp_data[index];
}

void MAX7219::clock_out(uint8_t reg, uint8_t data)
{
    digitalWrite(m_DCLK, LOW);
    shiftOut(m_DATA, m_DCLK, MSBFIRST, reg);
    digitalWrite(m_DCLK, LOW);
    shiftOut(m_DATA, m_DCLK, MSBFIRST, data);
    digitalWrite(m_CS, LOW);
    
}
void MAX7219::write_register(uint8_t reg, uint8_t data)
{
  for (int8_t dev=0; dev<m_device_count; dev++)
  {
      digitalWrite(m_CS, LOW);
      this->clock_out(reg, data);
      digitalWrite(m_CS, HIGH);
  }
}

void MAX7219::update()
{
    if (mp_data)
    {
        for (uint8_t digit=0; digit<8; digit++)
        {
            digitalWrite(m_CS, LOW);
            for (int8_t dev=(m_device_count-1); dev>=0; dev--)
            {
                uint8_t index = (digit * m_device_count) + dev;
                this->clock_out(eRegister_D0 + digit, mp_data[index]);
            }
            digitalWrite(m_CS, HIGH);
        }
    }
}

void MAX7219::clear_all()
{
    memset(mp_data, 0, m_device_count*8);
    this->update();
}

void MAX7219::set_decode(eDecodeMode eMode)
{
    this->write_register(eRegister_DecodeMode, (uint8_t)eMode);
}

void MAX7219::set_intensity(uint8_t intensity)
{
    if (intensity > 15)
    {
        intensity = 15;
    }
    this->write_register(eRegister_Intensity, intensity);
}

void MAX7219::set_scan_limit(uint8_t limit)
{
    if (limit > 7)
    {
        limit = 7;
    }
    this->write_register(eRegister_ScanLimit, limit);
}

void MAX7219::set_shutdown(bool shdn)
{
    this->write_register(eRegister_Shutdown, shdn ? 0x00 : 0x01);
}

void MAX7219::set_test(bool test)
{
    this->write_register(eRegister_Test, test ? 0x01 : 0x00);
}
