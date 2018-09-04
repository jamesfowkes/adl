#ifndef _ADL_UTIL_H_
#define _ADL_UTIL_H_

typedef struct
{
	char * buffer;
	uint16_t max_size;
} adl_string_buffer;

bool adl_convert_numeric_range(char const * const range, int32_t& min, int32_t& max, char ** pend);
bool adl_parse_single_numeric(char const * const numeric, int32_t& parsed, char ** pend);
uint8_t adl_parse_comma_separated_numerics(char const * const s, int32_t * presults);

#endif