#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <Arduino.h>

#include "adl.h"

/* Mocking for 'millis' function */
static unsigned long _millis;
unsigned long millis(void) { return _millis; }
void millis_set(unsigned long set) { _millis = set; }

/* Mocking for 'delay' function */
void delay(unsigned long ms) { (void)ms; }

/* Mocking for 'adl_board_send' function */
static char _sent[128]; 
void adl_board_send(char * to_send)
{
    strcpy(_sent, to_send);
}

/* Mocking for nonvolatile functionality */
static uint8_t _nonvolatile[1024];
static uint16_t s_next_nonvolatile_address = 0;
static uint8_t * last_write_addr;
static uint8_t * last_read_addr;

void adl_mock_nonvolatile_reset()
{
    s_next_nonvolatile_address = 0;
}

void adl_mock_nonvolatile_set(uint32_t location, uint32_t size, void * data)
{
    memcpy(&_nonvolatile[location], data, size);
}

uint8_t * adl_mock_nonvolatile_get_last_write()
{
    return last_write_addr;
}

uint8_t * adl_mock_nonvolatile_get_last_read()
{
    return last_read_addr;
}

void adl_nv_alloc(ADL_NV_LOCATION& to_alloc)
{
	to_alloc.address = s_next_nonvolatile_address;
	s_next_nonvolatile_address += to_alloc.size;
}

void adl_nv_load(void * dst, ADL_NV_LOCATION& load_from)
{
    if(dst)
    {
        last_read_addr = &_nonvolatile[load_from.address];
        memcpy(dst, last_read_addr, load_from.size);
    }
}

void adl_nv_save(void * src, ADL_NV_LOCATION& save_to)
{
    if(src)
    {
        last_write_addr = &_nonvolatile[save_to.address];
        memcpy(last_write_addr, src, save_to.size);
    }
}
