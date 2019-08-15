#ifndef _RAAT_UTIL_H_
#define _RAAT_UTIL_H_

typedef struct
{
    char * buffer;
    uint16_t max_size;
} raat_string_buffer;

bool string_is_valid_for_csv_numerics(char const * s);

bool raat_convert_numeric_range(char const * const range, int32_t& min, int32_t& max, char ** pend);

template <class RESULT_TYPE>
bool raat_parse_single_numeric(char const * const numeric, RESULT_TYPE& parsed, char ** p_end)
{
    if (!numeric) { return false; }

    char * p_local_end;
    int32_t local = strtol(numeric, &p_local_end, 10);

    if (p_local_end > numeric)
    {
        parsed = local;
        if (p_end)
        {
            *p_end = p_local_end;
        }
    }
    return (p_local_end > numeric);
}

template <class RESULT_TYPE>
uint8_t raat_parse_comma_separated_numerics(char const * const s, RESULT_TYPE * presults)
{
    if (!s) { return 0; }
    if (!presults) { return 0; }
    if (strlen(s) == 0) { return 0; }
    if (!string_is_valid_for_csv_numerics(s)) { return 0; }

    uint8_t count = 0;
    char const * p = s;
    bool converted;
    bool continue_with_conversion;

    do
    {
        converted = raat_parse_single_numeric<RESULT_TYPE>(p, presults[count], (char**)&p);
        if (converted) { count++; };
        
        continue_with_conversion = (*p==',');
        if (continue_with_conversion) {p++;}

    } while (converted && continue_with_conversion);

    return count;
}

char nibble_to_hex(uint8_t b);
void byte_to_hex(char * buffer, uint8_t b);

template <class INT_TYPE>
bool inrange(INT_TYPE a, INT_TYPE min_value, INT_TYPE max_value)
{
	return (a >= min_value) && (a <= max_value);
}

#endif
