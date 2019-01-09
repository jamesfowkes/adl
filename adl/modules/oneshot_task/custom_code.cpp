#include "adl.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"

static int some_data;
static void my_task_fn(ADLOneShotTask * pThisTask, void * pTaskData)
{
    Serial.print("Task run at ");
    Serial.print(millis());
    Serial.print("ms. Data = ");
    Serial.println(*(int*)pTaskData);
    pThisTask->start();
}

static ADLOneShotTask my_task(1000, my_task_fn, &some_data);

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    my_task.start();
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    my_task.run();
}
