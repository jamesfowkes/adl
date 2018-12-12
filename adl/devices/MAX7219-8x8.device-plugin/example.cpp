#include "adl.h"

#include "MAX7219.h"
#include "MAX7219-8x8.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"
#include "adl-task.h"

static MAX7219_8x8 * sp_max7219_8x8;

static const uint8_t NO_CELL = 0xFF;

static uint8_t s_row = 0;
static uint8_t s_col = 0;

void row_column_task_fn(ADLTask& this_task, void * pData)
{
    (void)this_task; (void)pData;

    if (s_row < 8)
    {
        sp_max7219_8x8->set(s_row, s_col, true);
    }
    else
    {
        sp_max7219_8x8->clear_all();
        s_col = 0xFF;
        s_row = 0xFF;
    }

    sp_max7219_8x8->update();

    incrementwithrollover(s_col, 15);
    if (s_col == 0)
    {
        incrementwithrollover(s_row, 8);
    }
}
static ADLTask s_row_column_task(100, row_column_task_fn, NULL);

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
    s_row_column_task.run();
}

