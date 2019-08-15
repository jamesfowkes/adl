#ifndef _RAAT_SERVO_H_
#define _RAAT_SERVO_H_

class RAATServo : public DeviceBase
{
public:
    RAATServo(int pin, uint8_t start_angle);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    void set(uint8_t degrees);

private:
    int m_pin;
    uint8_t m_start_angle;
    Servo m_servo;
};

#endif
