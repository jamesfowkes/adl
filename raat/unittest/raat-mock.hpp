#ifndef _RAAT_MOCK_H_
#define _RAAT_MOCK_H_

uint8_t * raat_mock_nonvolatile_get_last_write();
uint8_t * raat_mock_nonvolatile_get_last_read();

void raat_mock_nonvolatile_reset();
void raat_mock_nonvolatile_set(uint32_t location, uint32_t size, void * data);

#endif