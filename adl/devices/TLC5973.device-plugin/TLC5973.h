#include "Arduino.h"

class TLC5973  : public DeviceBase
{
 public:
    TLC5973(uint16_t n,uint8_t p);
    void setPixelColor(uint16_t n, uint16_t r, uint16_t g, uint16_t b);
    void show();
    void begin();
    void clear();

    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    void tick();

 private:

    int handle_command(char const * const command, char * reply);
    void set_pixels(uint8_t range_min, uint8_t range_max, uint16_t r, uint16_t g, uint16_t b);
    void dump_pixels();

    void updateLength();
    void pulse(); 
    void writeZero();
    void writeNone();
    void writeOne();
    void waitGSLAT();
    void writeWord(uint16_t word);
    void writePixel(uint16_t r, uint16_t g, uint16_t b);

    uint16_t m_npixels;       // Number of RGB LEDs in strip
    uint16_t m_numWords;      // Size of 'pixels' buffer below (3 or 4 bytes/pixel)
    uint16_t *mp_pixels;        // Holds LED color values (3 or 4 bytes each)
      
    uint8_t m_pin;     

    volatile uint8_t *mp_port;         // Output PORT register
    uint8_t m_pinMask;
    
};
