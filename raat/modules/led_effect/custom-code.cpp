#include <Adafruit_NeoPixel.h>

#include "raat.hpp"

#include "adafruit-neopixel-raat.hpp"
#include "led-effect.hpp"

static void value_provider(uint8_t index, uint8_t * pMultiplier, uint8_t * pDivisor)
{
    uint8_t multiplier = index+1;
    *pMultiplier = multiplier * multiplier;
    *pDivisor = ((NLEDS + 1) * (NLEDS + 1)) / 6;
}

static uint8_t s_led_values[NLEDS][3] = {0};
LarsonScanner s_larson = LarsonScanner((uint8_t*)s_led_values, NLEDS, 5, value_provider);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    s_larson.start(128,96,128);
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    for (uint8_t i=0;i<NLEDS;i++)
    {
        devices.pNeoPixels->setPixelColor(i, s_led_values[i][0], s_led_values[i][1], s_led_values[i][2]);
    }
    devices.pNeoPixels->show();
    s_larson.update();
	delay(75);
}
