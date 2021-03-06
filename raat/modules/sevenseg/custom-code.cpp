#include "raat.hpp"

#include "sevenseg.hpp"

#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"
#include "raat-task.hpp"

static SevenSeg s_sevenseg = SevenSeg(
    0,1,2,3,4,5,6,7
);

static const uint8_t s_pin_mapping[] = {
    10,9,8,7,6,5,4
};

static uint8_t digit = 0;
static void my_task_fn(RAATTask& this_task, void * pTaskData)
{
    (void)this_task; (void)pTaskData;
    uint8_t bitmap = s_sevenseg.get_bitmap_for_digit(digit, false, false);
    for (uint8_t pin = 0; pin < 7; pin++)
    {
        digitalWrite(s_pin_mapping[pin], bitmap & (1 << pin));
    }
    
    incrementwithrollover(digit, 0x0F);
}
static RAATTask my_task(250, my_task_fn, NULL);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    for (uint8_t pin = 0; pin < 7; pin++)
    {
        pinMode(s_pin_mapping[pin], OUTPUT);
    }
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    my_task.run();
}
