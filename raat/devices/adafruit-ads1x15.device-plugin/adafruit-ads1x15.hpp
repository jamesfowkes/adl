#ifndef _RAAT_ADAFRUIT_ADS1X15_H_
#define _RAAT_ADAFRUIT_ADS1X15_H_

#include <Adafruit_ADS1015.h>

enum ads_reading_type
{
    ADS_READING_RAW,
    ADS_READING_MV,
    ADS_READING_SCALED
};
typedef enum ads_reading_type ADS_READING_TYPE;

enum adc_subtype {
    ADC_SUBTYPE_ADS1015,
    ADC_SUBTYPE_ADS1115
};
typedef enum adc_subtype ADC_SUBTYPE;

class Adafruit_ADS1x15 : public DeviceBase
{
public:
    Adafruit_ADS1x15(ADC_SUBTYPE ads_subtype, float multiplier);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);
    
    unsigned long get_reading(uint8_t channel, ADS_READING_TYPE type);

private:
    float m_multiplier;
    ADC_SUBTYPE m_ads_subtype;
    void * mp_adc;
    
    uint8_t m_channel;

    uint8_t handle_query_command(char const * const command, char * reply);
    uint8_t handle_setting_command(char const * const command, char * reply);

    unsigned long get_raw_value(uint8_t channel);
};

#endif