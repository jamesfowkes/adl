#include "raat.h"

#include "raat-oneshot-timer.h"
#include "raat-oneshot-task.h"
#include "raat-task.h"

static int some_data;
static void my_task_fn(void * pTaskData)
{
    Serial.print("Task run at ");
    Serial.print(millis());
    Serial.print("ms. Data = ");
    Serial.println(*(int*)pTaskData);
}

static RAATTask my_task(1000, my_task_fn, &some_data);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    my_task.run();
}
