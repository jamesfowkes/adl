#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

#include "raat-oneshot-timer.hpp"

typedef enum startup_state
{
	STARTUP_STATE_LOW,
	STARTUP_STATE_HIGH,
	STARTUP_STATE_TRISTATE,
    STARTUP_STATE_PU
} estartup_state;

class DigitalOutput : public DeviceBase
{
public:
    DigitalOutput(int pin, estartup_state startupState);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    void set(bool on, uint16_t timeout=0);
    void toggle(uint16_t timeout=0);
    bool state(void);
    void tristate(bool pullup);

private:

    int m_pin;
    
    estartup_state m_startup_state;
    RAATOneShotTimer m_timeout;

    void start_timeout(uint16_t timeout);
};

#endif
