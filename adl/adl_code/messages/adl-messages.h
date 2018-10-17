#ifndef _ADL_MESSAGES_H_
#define _ADL_MESSAGES_H_

int adl_msg_invalid_range(char * reply);
int adl_msg_invalid_values(char * reply);
int adl_msg_wrong_number_of_values(char * reply, uint8_t parsed_count, char const * const s);

#endif
