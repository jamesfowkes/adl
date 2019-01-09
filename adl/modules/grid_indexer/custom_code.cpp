#include <Adafruit_NeoPixel.h>

#include "adl.h"

#include "adafruit-neopixel-adl.h"
#include "grid-indexer.h"

static GridIndexer s_indexer = GridIndexer(3);

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    for (uint8_t i = 0; i<9; i++)
    {
    	devices.pNeoPixels->setPixelColor(s_indexer.get(i), 32, 32, 32);
    	devices.pNeoPixels->show();
    	delay(200);
    }

	devices.pNeoPixels->clear();
	devices.pNeoPixels->show();
}
