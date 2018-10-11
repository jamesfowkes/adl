#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <Arduino.h>

/* Mocking for 'millis' function */
unsigned long _millis;
unsigned long millis(void) { return _millis; }
void millis_set(unsigned long set) { _millis = set; }
