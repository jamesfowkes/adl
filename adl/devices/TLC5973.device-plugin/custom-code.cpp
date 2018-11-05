#include "adl.h"

#include <TLC5973.h>
//#include "TLC5973.h"
#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"
#include "adl-task.h"

TLC5973 s_TLC5973 = TLC5973(8,5);

static void my_task_fn(ADLTask& pThisTask, void * pTaskData)
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
	    	s_TLC5973.setPixelColor(j, (r[j] * i)/100, (g[j] * i)/100, (b[j] * i)/100);
	    }
        //s_TLC5973.setPixelColor(0, (r[0] * i)/100, (g[0] * i)/100, (b[0] * i)/100);
        //s_TLC5973.setPixelColor(1, (r[1] * i)/100, (g[1] * i)/100, (b[1] * i)/100);
        //s_TLC5973.setPixelColor(2, (r[2] * i)/100, (g[2] * i)/100, (b[2] * i)/100);
        //s_TLC5973.setPixelColor(3, (r[3] * i)/100, (g[3] * i)/100, (b[3] * i)/100);
        //s_TLC5973.setPixelColor(4, (r[4] * i)/100, (g[4] * i)/100, (b[4] * i)/100);
        //s_TLC5973.setPixelColor(5, (r[5] * i)/100, (g[5] * i)/100, (b[5] * i)/100);
        //s_TLC5973.setPixelColor(6, (r[6] * i)/100, (g[6] * i)/100, (b[6] * i)/100);
        //s_TLC5973.setPixelColor(7, (r[7] * i)/100, (g[7] * i)/100, (b[7] * i)/100);
        s_TLC5973.show();
        delay(25);
    }
    Serial.println(r[0]);
    Serial.println(g[0]);
    Serial.println(b[0]);
	/*(void)pThisTask; (void)pTaskData;

	uint16_t r;
    uint16_t g;
    uint16_t b;

    for (uint8_t i = 0; i<8;i++)
    {
	    r = random(64, 256);
	    g = random(64, 256);
	    b = random(64, 256);

	    s_TLC5973.setPixelColor(i, r, g, b);
	}
    s_TLC5973.show();*/
    adl_logln(LOG_ADL, "Task");
}
static ADLTask my_task(5000, my_task_fn, NULL);

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)ndevices; (void)pparams; (void)nparams;

    //pTLC5973 = (TLC5973*)pdevices[0];
	s_TLC5973.begin();
    s_TLC5973.clear();
    s_TLC5973.show();

    my_task.start();
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
    my_task.run();
}
