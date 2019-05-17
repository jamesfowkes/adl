#include "raat.hpp"

#include "MT8870.hpp"

static char phone_number[12] = "";
static uint8_t count = 0;

static void reset()
{
    count = 0;
    phone_number[count] = '\0';
}

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
  (void)devices; (void)params;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)params;
    
    uint8_t number = devices.pMT8870->get();

    if (number != NO_PRESS)
    {
        phone_number[count++] = press_to_char(number);
        phone_number[count] = '\0';

        if (count == 11)
        {
            raat_logln(LOG_APP, "Dialled: %s", phone_number);
            reset();
        }
    }
}
