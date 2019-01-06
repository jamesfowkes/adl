#ifndef _ENC28J60ADL_H_
#define _ENC28J60ADL_H_

class ENC28J60ADL : public DeviceBase
{
public:
    ENC28J60ADL();
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
private:
    int m_pin;
};

#endif
