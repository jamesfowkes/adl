#include <Servo.h>

#include "raat.hpp"

#include "servo.hpp"

RAATServo::RAATServo(int pin, uint8_t startupangle) :
    m_pin(pin), m_start_angle(startupangle)
{
}

void RAATServo::tick() {}

void RAATServo::reset()
{
    m_servo.write(m_start_angle);
}

void RAATServo::setup()
{
    m_servo.attach(m_pin);
    this->reset();
}

uint16_t RAATServo::command_handler(char const * const command, char * reply)
{
    int32_t setting_degrees;
    bool ok = false;

    if ((ok = raat_parse_single_numeric(&command[1], setting_degrees, NULL)))
    {
        if (inrange<int32_t>(setting_degrees, 0, 180))
        {
            this->set((uint8_t)setting_degrees);
            strcpy(reply, "OK");            
        }
    }

    if (ok)
    {
        return strlen(reply);
    }
    else
    {
        strcpy(reply, "?");
        return 2;
    }
}

void RAATServo::set(uint8_t degrees)
{
    m_servo.write(degrees);
}
