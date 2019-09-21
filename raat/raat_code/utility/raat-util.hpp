#ifndef _RAAT_UTIL_H_
#define _RAAT_UTIL_H_

typedef struct
{
    char * buffer;
    uint16_t max_size;
} raat_string_buffer;

bool string_is_valid_for_delimited_numerics(char const * s, char delimiter);

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
uint8_t raat_parse_delimited_numerics(
    char const * const s, RESULT_TYPE * presults, char delimiter, uint8_t max_to_convert=0)
{
    if (!s) { return 0; }
    if (!presults) { return 0; }
    if (strlen(s) == 0) { return 0; }
    if (!string_is_valid_for_delimited_numerics(s, delimiter)) { return 0; }

    uint8_t count = 0;
    char const * p = s;
    bool converted;
    bool continue_with_conversion;

    do
    {
        converted = raat_parse_single_numeric<RESULT_TYPE>(p, presults[count], (char**)&p);
        if (converted) { count++; };
        
        if ((max_to_convert > 0) && (count == max_to_convert))
        {
            continue_with_conversion = false;
        }
        else
        {
            continue_with_conversion = (*p==delimiter);
        }

        if (continue_with_conversion) {p++;}

    } while (converted && continue_with_conversion);

    return count;
}

template <class RESULT_TYPE>
uint8_t raat_parse_comma_separated_numerics(char const * const s, RESULT_TYPE * presults, uint8_t max_to_convert=0)
{
    return raat_parse_delimited_numerics<RESULT_TYPE>(s, presults, ',', max_to_convert);
}

char nibble_to_hex(uint8_t b);
void byte_to_hex(char * buffer, uint8_t b);

template <class INT_TYPE>
bool inrange(INT_TYPE a, INT_TYPE min_value, INT_TYPE max_value)
{
	return (a >= min_value) && (a <= max_value);
}

/* Array Utils */
bool any_are_null(void * ptrs[], const int n);

template <class PTR_TYPE>
bool all_match(PTR_TYPE const * const pvals, int n)
{
    bool match = false;
    if (pvals && n)
    {
        match = true;
        for (int i=1; i<n; i++)
        {
            if (pvals[0] != pvals[i])
            {
                match = false;
                break;
            }
        }
    }
    return match;
}

template <class ARRAY_TYPE>
uint8_t count_values(ARRAY_TYPE * haystack, ARRAY_TYPE needle, int n)
{
    uint8_t count = 0;
    if (haystack && n)
    {       
        for (int i=0; i<n; i++)
        {
            if (haystack[i] == needle) { count++; }
        }
    }
    return count;
}

template <class ARRAY_TYPE>
bool array_contains(ARRAY_TYPE * haystack, ARRAY_TYPE needle, int n)
{
    bool found = false;
    if (haystack && n)
    {     
        for (int i=0; i<n; i++)
        {
            if (haystack[i] == needle)
            {
                found = true;
                break;
            }
        }
    }
    return found;
}

template <class ARRAY_TYPE>
bool all_unique(ARRAY_TYPE * vals, int n)
{
    bool unique = false;
    if (vals && n)
    {
        unique = true;
        for (int i=0; i<n; i++)
        {
            if (array_contains<ARRAY_TYPE>(&vals[i+1], vals[i], n-i-1))
            {
                unique = false;
                break;
            }
        }
    }
    return unique;
}

#endif
