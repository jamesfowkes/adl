#include "adl.h"

#include "MAX7219.h"

static MAX7219 * sp_max7219;

static uint8_t s_count = 0;
static uint8_t s_dot_count_data[16] = {0};
static uint8_t s_pixel_data[16] = {0};

static const uint8_t OUTPUT_BYTES[] = 
{
  0b00000000,
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
    uint8_t dot = s_count % 16;

    uint8_t data_index = (dot < 8) ? row : 8 + row;

    s_dot_count_data[data_index]++;   

    for (uint8_t px=0; px < 16; px++)
    {
        s_pixel_data[px] = OUTPUT_BYTES[s_dot_count_data[px]];
    }

    sp_max7219->Set(s_pixel_data);
    
    delay(100);
    
    s_count++;
    if (s_count == 128)
    {
      s_count = 0;
      memset(s_dot_count_data, 0, 16);
      sp_max7219->ClearAll();
    }


    /*s_pixel_data[0] = OUTPUT_BYTES[s_count];
    sp_max7219->Set(s_pixel_data);
    
    delay(100);

    s_count++;
    if (s_count == 8)
    {
      s_count = 0;
      memset(s_dot_count_data, 0, 16);
      sp_max7219->ClearAll();
      delay(100);
    }*/
}
