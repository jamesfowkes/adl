#include "raat.hpp"

#include "TLC5973.hpp"
#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"
#include "raat-task.hpp"

TLC5973 * pTLC5973;

static void my_task_fn(RAATTask& pThisTask, void * pTaskData)
{
	uint16_t r[8];
    uint16_t g[8];
    uint16_t b[8];

    for (uint8_t i = 0; i<8;i++)
    {
    	r[i] = random(64, 256);
    	g[i] = random(64, 256);
    	b[i] = random(64, 256);
    }

    for(uint32_t i=0; i<100; i++)
    {
	    for (uint8_t j = 0; j<8;j++)
	    {
	    	pTLC5973->setPixelColor(j, (r[j] * i)/100, (g[j] * i)/100, (b[j] * i)/100);
	    }
        pTLC5973->show();
        delay(25);
    }
    Serial.println(r[0]);
    Serial.println(g[0]);
    Serial.println(b[0]);
}
static RAATTask my_task(5000, my_task_fn, NULL);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    pTLC5973 = devices.pTLC5973;

    my_task.start();
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    my_task.run();
}
