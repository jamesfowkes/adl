#ifndef _RAAT_TIME_H_
#define _RAAT_TIME_H_

struct raat_time
{
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;
};
typedef struct raat_time RAAT_TIME;

void raat_time_get_system_time(RAAT_TIME& t);
bool raat_time_times_are_equal(RAAT_TIME& t1, RAAT_TIME& t2);

#endif
