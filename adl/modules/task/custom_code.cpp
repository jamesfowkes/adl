#include "adl.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"
#include "adl-task.h"

static int some_data;
static void my_task_fn(void * pTaskData)
{
    Serial.print("Task run at ");
    Serial.print(millis());
    Serial.print("ms. Data = ");
    Serial.println(*(int*)pTaskData);
}

static ADLTask my_task(1000, my_task_fn, &some_data);

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    my_task.run();
}
