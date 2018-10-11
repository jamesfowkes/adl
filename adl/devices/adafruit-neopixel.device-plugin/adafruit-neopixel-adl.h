#ifndef _ADAFRUIT_NEOPIXEL_ADL_H_
#define _ADAFRUIT_NEOPIXEL_ADL_H_

class AdafruitNeoPixelADL : public DeviceBase
{
public:
	AdafruitNeoPixelADL(uint8_t pin, uint16_t npixels);
	void setup();
	void reset();
	void tick();
	int command_handler(char const * const command, char * reply);
	Adafruit_NeoPixel& pixels();
private:
	int handle_command(char const * const command, char * reply);
	void set_pixels(uint8_t range_min, uint8_t range_max, uint8_t r, uint8_t g, uint8_t b);
	Adafruit_NeoPixel m_pixels;
	uint8_t m_npixels;
};

#endif