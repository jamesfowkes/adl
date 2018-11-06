#ifndef _ADL_MOCK_H_
#define _ADL_MOCK_H_

uint8_t * adl_mock_nonvolatile_get_last_write();
uint8_t * adl_mock_nonvolatile_get_last_read();

void adl_mock_nonvolatile_reset();
void adl_mock_nonvolatile_set(uint32_t location, uint32_t size, void * data);

#endif