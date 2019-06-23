#ifndef _CSVLOG_H_
#define _CSVLOG_H_

#define N_FIELDS (5)

typedef enum _eCSVDataType
{
	eCSVDataType_char,
	eCSVDataType_u8,
	eCSVDataType_u16,
	eCSVDataType_u32,
	eCSVDataType_u64,
	eCSVDataType_s8,
	eCSVDataType_s16,
	eCSVDataType_s32,
	eCSVDataType_s64,
	eCSVDataType_str,
	eCSVDataType_float,
	eCSVDataType_double,
	eCSVDataType_ptr
} eCSVDataType;

typedef int (*print_function)(const char * format, ... );

void CSVLog_Init(print_function pfn_printer);
void CSVLog_AddField(void * pField, eCSVDataType CSVDataType, char const * formatter);
void CSVLog_PrintNow();

#endif