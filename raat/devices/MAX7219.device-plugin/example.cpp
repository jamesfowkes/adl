#include "raat.h"

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

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    sp_max7219 = devices.pMAX7219_Example;
    sp_max7219->set_shutdown(false);
    sp_max7219->set_intensity(5);
    sp_max7219->set_scan_limit(7);
    sp_max7219->set_test(false);
    sp_max7219->clear_all();
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    uint8_t row = s_count / 16;
    uint8_t device = (s_count % 16) >= 8 ? 1 : 0;
    uint8_t data = s_count % 8;

    sp_max7219->set(device, row, OUTPUT_BYTES[data]);
    sp_max7219->update();

    delay(100);
    
    s_count++;
    if (s_count == 128)
    {
      s_count = 0;
      sp_max7219->clear_all();
    }
}
