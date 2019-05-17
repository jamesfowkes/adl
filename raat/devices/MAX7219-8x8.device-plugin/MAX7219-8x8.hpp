#ifndef _MAX7219_8X8_H_
#define _MAX7219_8X8_H_

class MAX7219_8x8 : public DeviceBase
{
public:
    MAX7219_8x8(uint8_t cs, uint8_t din, uint8_t dclk, uint8_t device_count);
    void reset();
    void tick();
    void setup();
    uint16_t command_handler(char const * const command, char * reply);
    void set(uint8_t row, uint8_t col, bool set);
    void update();
    void clear_all();
    void set_intensity(uint8_t intensity);
    void set_shutdown(bool shdn);
    void set_test(bool test);
private:
    MAX7219 m_max7219;
};

#endif