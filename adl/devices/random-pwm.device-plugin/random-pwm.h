#ifndef _RANDOM_PWM_H_
#define _RANDOM_PWM_H_

class RandomPWM : public DeviceBase
{
public:
    RandomPWM(int pin, unsigned long interval, int low_limit, int high_limit);
    void setup();
    void reset();
    int command_handler(char const * const command, char * reply);
    void tick();
    
private:
    int m_pin;
    int m_level;
    unsigned long m_llimit;
    unsigned long m_hlimit;
    unsigned long m_interval;
    unsigned long m_last_time;
};

#endif