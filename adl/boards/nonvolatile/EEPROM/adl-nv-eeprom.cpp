/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * Arduino Includes
 */

#include <EEPROM.h>

/*
 * ADL Includes
 */

#include "adl.h"

/*
 * Private Variables
 */

static uint16_t s_next_eeprom_address = 0;

/*
 * Public Functions
 */

void adl_nonvolatile_setup()
{

}

void adl_nv_alloc(ADL_NV_LOCATION& to_alloc)
{
	to_alloc.address = s_next_eeprom_address;
	s_next_eeprom_address += to_alloc.size;
}

void adl_nv_load(void * dst, ADL_NV_LOCATION& load_from)
{
    uint8_t i;
    if(dst)
    {
        for (i=0; i<load_from.size; i++)
        {
            *((byte*)(dst)+i) = EEPROM.read(load_from.address + i);
        }
    }
}

void adl_nv_save(void * src, ADL_NV_LOCATION& save_to)
{
    uint8_t i;
    if(src)
    {
        for (i=0; i<save_to.size; i++)
        {
            EEPROM.update(save_to.address + i, *((byte*)(src)+i));
        }
    }
}
