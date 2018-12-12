#include "adl.h"

#include "MAX7219.h"
#include "MAX7219-8x8.h"

static MAX7219_8x8 * sp_max7219_8x8;

static uint8_t s_row = 0;
static uint8_t s_col = 0;

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)ndevices; (void)pparams; (void)nparams;
    sp_max7219_8x8 = (MAX7219_8x8*)pdevices[0];
    sp_max7219_8x8->set_shutdown(false);
    sp_max7219_8x8->set_intensity(5);
    sp_max7219_8x8->set_test(false);
    sp_max7219_8x8->clear_all();
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
    
    sp_max7219_8x8->set(s_row, s_col, true);
    sp_max7219_8x8->update();
    delay(100);

    incrementwithrollover(s_col, 16);

    if (s_col == 0)
    {
        incrementwithrollover(s_row, 8);
        if (s_row == 0)
        {
            sp_max7219_8x8->clear_all();      
            delay(100);
        }
    }
}

