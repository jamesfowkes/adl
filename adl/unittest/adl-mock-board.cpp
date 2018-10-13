#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <Arduino.h>

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
