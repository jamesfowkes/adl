#include <Arduino.h>

#include "adl-defs.h"
#include "adl-nv.h"
#include "device.h"
#include "parameter.h"
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

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    my_task.start();
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

    my_task.run();
}
