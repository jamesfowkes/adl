#ifndef _ENC28J60_H_
#define _ENC28J60_H_

class ENC28J60 : public DeviceBase
{
public:
    ENC28J60();
    void setup();
    void reset();
    void tick();
    int command_handler(char const * const command, char * reply);
    
private:
    int m_pin;
};

#endif
