#ifndef _MAX7219_H_
#define _MAX7219_H_

typedef enum _eDecodeMode
{
    eDecodeMode_None,
    eDecodeMode_CodeBDigit0,
    eDecodeMode_CodeBDigits3_0,
    eDecodeMode_CodeBDigits7_0
} eDecodeMode;

class MAX7219 : public DeviceBase
{
public:
    MAX7219(uint8_t cs, uint8_t din, uint8_t dclk, uint8_t device_count);

    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);

    void set(uint8_t device, uint8_t digit, uint8_t data);
    uint8_t get(uint8_t device, uint8_t digit);

    void update();
    void set_decode(eDecodeMode eMode);
    void set_intensity(uint8_t intensity);
    void set_scan_limit(uint8_t limit);
    void set_shutdown(bool shdn);
    void set_test(bool test);
    void clear_all();
    void clock_out(uint8_t reg, uint8_t data);

private:
    void write_register(uint8_t reg, uint8_t data);

    uint8_t m_CS;
    uint8_t m_DATA;
    uint8_t m_DCLK;
    uint8_t m_device_count;
    uint8_t *mp_data;
};

#endif
