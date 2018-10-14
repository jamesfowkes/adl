#include <Arduino.h>

#include <Wire.h>
#include <IRremote.h>

#include "parameter.h"
#include "device.h"
#include "adl.h"

#include "ir-receiver.h"

static bool command_is_query(char const * const command)
{
    int command_length = strlen(command);
    return command[command_length-1] == '?';
}

static bool command_is_setting(char const * const command)
{
    return (command[0] == 'C') && (command[1] == 'H');
}

/*
 * Class Private Functions
 */

uint8_t Adafruit_ADS1x15::handle_query_command(char const * const command, char * reply)
{
    unsigned long adc_value;

    if (strcmp(command, "?") == 0)
    {
        adc_value = this->get_reading(m_channel, ADS_READING_RAW);
    }
    else if (strcmp(command, "pin?") == 0)
    {
        adc_value = this->get_reading(m_channel, ADS_READING_MV);
    }
    else if (strcmp(command, "mv?") == 0)
    {
        adc_value = this->get_reading(m_channel, ADS_READING_SCALED);
    }
    else
    {
        reply[0] = '?';
        return 1;
    }

    sprintf(reply, "%lu", adc_value);
    return strlen(reply);
}

uint8_t Adafruit_ADS1x15::handle_setting_command(char const * const command, char * reply)
{
    uint8_t channel = command[2] - '0';

    if (channel < 4)
    {
        m_channel = channel;
        strcpy(reply, "SOK");
        return strlen(reply);
    }
    else
    {
        reply[0] = '?';
        return 1;
    }
}

/*
 * Class Public Functions
 */

IR_Receiver::IR_Receiver(uint8_t pin) : m_irrecv(RECV_PIN);
{

}

void Adafruit_ADS1x15::reset()
{
    
}

void Adafruit_ADS1x15::tick()
{

}

void Adafruit_ADS1x15::setup()
{
    this->reset();
    Wire.begin();
    switch(m_ads_subtype)
    {
    case ADC_SUBTYPE_ADS1015:
        ((Adafruit_ADS1015*)mp_adc)->begin();
        break;
    case ADC_SUBTYPE_ADS1115:
        ((Adafruit_ADS1115*)mp_adc)->begin();
        break;
    }
}

int Adafruit_ADS1x15::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;

    if (command_is_query(command))
    {
        reply_length = handle_query_command(command, reply);
    }
    else if (command_is_setting(command))
    {
        reply_length = handle_setting_command(command, reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

unsigned long Adafruit_ADS1x15::get_reading(uint8_t channel, ADS_READING_TYPE type)
{
    unsigned long adc_value = this->get_raw_value(channel);

    switch(type)
    {
    case ADS_READING_RAW:
        break;
    case ADS_READING_MV:
        adc_value *= READING_TO_MILLIVOLTS_MULTIPLIER;
        break;
    case ADS_READING_SCALED:
        adc_value *= (READING_TO_MILLIVOLTS_MULTIPLIER * m_multiplier);
        break;
    }
    return adc_value;
}