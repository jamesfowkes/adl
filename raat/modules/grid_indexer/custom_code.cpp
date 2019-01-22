#include <Adafruit_NeoPixel.h>

#include "raat.h"

#include "adafruit-neopixel-raat.h"
#include "grid-indexer.h"

static GridIndexer s_indexer = GridIndexer(3);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
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
