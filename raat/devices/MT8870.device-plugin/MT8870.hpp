#ifndef _MT8870_H_
#define _MT8870_H_

#define NO_PRESS 0xFF

char press_to_char(uint8_t press);

class MT8870 : public DeviceBase
{
public:
    MT8870(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t trig);
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    uint8_t get();
    uint8_t peek();

private:
    uint8_t m_code_pins[4];
    uint8_t m_trig_pin;
    bool m_triggered;

    uint8_t m_presses[4];
    
    void wait_for_release();
    void check_and_handle_press();

    void store_press(uint8_t press);
};

#endif
