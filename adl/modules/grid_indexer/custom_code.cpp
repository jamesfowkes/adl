#include <Adafruit_NeoPixel.h>

#include "adl.h"

#include "adafruit-neopixel-adl.h"
#include "grid-indexer.h"

static GridIndexer s_indexer = GridIndexer(3);

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
    (void)pdevices; (void)ndevices; (void)pparams; (void)nparams;

	AdafruitNeoPixelADL* pPixels = (AdafruitNeoPixelADL*)pparams[0];

    for (uint8_t i = 0; i<9; i++)
    {
    	pPixels->setPixelColor(s_indexer.get(i), 32, 32, 32);
    	pPixels->show();
    	delay(200);
    }

	pPixels->clear();
	pPixels->show();
}
