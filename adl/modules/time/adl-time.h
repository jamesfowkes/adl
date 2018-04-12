#ifndef _ADL_TIME_H_
#define _ADL_TIME_H_

struct adl_time
{
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
};
typedef struct adl_time ADL_TIME;

void adl_time_get_system_time(ADL_TIME& t);
bool adl_time_times_are_equal(ADL_TIME& t1, ADL_TIME& t2);

#endif
