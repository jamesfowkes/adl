#include "adl.h"

#include "MAX7219.h"

static MAX7219 * sp_max7219;

static uint8_t count = 0;

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
    uint8_t row = count / 8;
    uint8_t outputs = OUTPUT_BYTES[count % 8];
    
    sp_max7219->SetOutputs(row, outputs);
    
    delay(100);
    
    count++;
    if (count == 64)
    {
      count = 0;
      sp_max7219->ClearAll();
    }
}

