#ifndef _RAAT_ONESHOT_TIMER_H_
#define _RAAT_ONESHOT_TIMER_H_

class RAATOneShotTimer
{
public:
    RAATOneShotTimer(uint16_t period);
    void start(uint16_t period = 0);
    bool check();
    void reset();
    bool check_and_reset();
    bool check_and_restart();
    bool is_running();
    void set_period(uint16_t period);
    
private:
    unsigned long m_start;
    uint16_t m_period;
    bool m_running;
};

#endif
