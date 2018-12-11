#include "adl.h"

#include "MAX7219.h"

static MAX7219 * sp_max7219;

static uint8_t s_count = 0;

static const uint8_t OUTPUT_BYTES[] = 
{
  0b00000001,
  0b00000011,
  0b00000111,
  0b00001111,
  0b00011111,
  0b00111111,
  0b01111111,
  0b11111111,
};

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)ndevices; (void)pparams; (void)nparams;
    sp_max7219 = (MAX7219*)pdevices[0];
    sp_max7219->SetShutdown(false);
    sp_max7219->SetIntensity(5);
    sp_max7219->SetScanLimit(7);
    sp_max7219->SetTest(false);
    sp_max7219->ClearAll();
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    uint8_t row = s_count / 16;
    uint8_t device = (s_count % 16) >= 8 ? 1 : 0;
    uint8_t data = s_count % 8;

    sp_max7219->Set(device, row, OUTPUT_BYTES[data]);
    sp_max7219->Update();

    delay(100);
    
    s_count++;
    if (s_count == 128)
    {
      s_count = 0;
      sp_max7219->ClearAll();
    }
}
