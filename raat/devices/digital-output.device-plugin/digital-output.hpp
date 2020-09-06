#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

typedef enum startup_state
{
	STARTUP_STATE_LOW,
	STARTUP_STATE_HIGH,
	STARTUP_STATE_TRISTATE
} estartup_state;

class DigitalOutput : public DeviceBase
{
public:
    DigitalOutput(uint8_t pin, estartup_state startupState);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    void set(bool on, uint16_t timeout=0);
    void toggle(uint16_t timeout=0);
    bool state(void);
    void tristate();

    uint8_t pin();

private:

    struct
    {
        uint16_t time;
        bool active;
    } m_timeout;

    uint8_t m_pin;
    void start_timeout(uint16_t timeout);
    estartup_state m_startup_state;
};

#endif
