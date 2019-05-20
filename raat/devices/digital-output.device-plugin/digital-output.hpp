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
    DigitalOutput(int pin, estartup_state startupState);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    void set(bool on);
    bool state(void);
    void tristate();

private:
    int m_pin;
    estartup_state m_startup_state;
};

#endif
