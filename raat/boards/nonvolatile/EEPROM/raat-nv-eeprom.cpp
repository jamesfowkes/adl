/*
 * C/C++ Includes
 */

#include <stdint.h>

/*
 * Arduino Includes
 */

#include <EEPROM.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

/*
 * Private Variables
 */

static uint16_t s_next_eeprom_address = 0;

/*
 * Public Functions
 */

void raat_nonvolatile_setup()
{

}

void raat_nv_alloc(RAAT_NV_LOCATION& to_alloc)
{
	to_alloc.address = s_next_eeprom_address;
	s_next_eeprom_address += to_alloc.size;
}

void raat_nv_load(void * dst, RAAT_NV_LOCATION& load_from)
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

void raat_nv_save(void * src, RAAT_NV_LOCATION& save_to)
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
