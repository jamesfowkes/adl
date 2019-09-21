#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <Arduino.h>

#include "raat.hpp"

/* Mocking for 'millis' function */
static unsigned long _millis;
unsigned long millis(void) { return _millis; }
void millis_set(unsigned long set) { _millis = set; }

/* Mocking for 'delay' function */
void delay(unsigned long ms) { (void)ms; }

/* Mocking for 'raat_board_send' function */
static char _sent[128]; 
void raat_board_send(char * to_send)
{
    strcpy(_sent, to_send);
}

/* Mocking for nonvolatile functionality */
static uint8_t _nonvolatile[1024];
static uint16_t s_next_nonvolatile_address = 0;
static uint8_t * last_write_addr;
static uint8_t * last_read_addr;

void raat_mock_nonvolatile_reset()
{
    s_next_nonvolatile_address = 0;
}

void raat_mock_nonvolatile_set(uint32_t location, uint32_t size, void * data)
{
    memcpy(&_nonvolatile[location], data, size);
}

uint8_t * raat_mock_nonvolatile_get_last_write()
{
    return last_write_addr;
}

uint8_t * raat_mock_nonvolatile_get_last_read()
{
    return last_read_addr;
}

void raat_nv_alloc(RAAT_NV_LOCATION& to_alloc)
{
	to_alloc.address = s_next_nonvolatile_address;
	s_next_nonvolatile_address += to_alloc.size;
}

void raat_nv_load(void * dst, RAAT_NV_LOCATION& load_from)
{
    if(dst)
    {
        last_read_addr = &_nonvolatile[load_from.address];
        memcpy(dst, last_read_addr, load_from.size);
    }
}

void raat_nv_save(void * src, RAAT_NV_LOCATION& save_to)
{
    if(src)
    {
        last_write_addr = &_nonvolatile[save_to.address];
        memcpy(last_write_addr, src, save_to.size);
    }
}

int raat_board_strlen_progmem(char const * s)
{
    return (int)strlen(s);
}

int raat_board_strncmp_progmem(char const * const pMemory, char const * const pProgmem, size_t len)
{
    return (int)strncmp(pMemory, pProgmem, len);
}

void raat_board_memcpy_progmem(char * pMemory, char const * const pProgmem, size_t len)
{
    memcpy(pMemory, pProgmem, len);
}
