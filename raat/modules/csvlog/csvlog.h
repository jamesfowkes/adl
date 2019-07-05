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

typedef struct _field
{
	void * pFieldValue;
	eCSVDataType eType;
	char const * pFormatter;
} Field;

class CSVLog
{
public:
	CSVLog(print_function pfn_printer, char const * prefix=NULL);
	void AddField(void * pField, eCSVDataType CSVDataType, char const * formatter);
	void PrintNow(void);

private:

	void print_char(char const * pFmt, void * pToPrint);
	void print_u8(char const * pFmt, void * pToPrint);
	void print_u16(char const * pFmt, void * pToPrint);
	void print_u32(char const * pFmt, void * pToPrint);
	void print_u64(char const * pFmt, void * pToPrint);
	void print_s8(char const * pFmt, void * pToPrint);
	void print_s16(char const * pFmt, void * pToPrint);
	void print_s32(char const * pFmt, void * pToPrint);
	void print_s64(char const * pFmt, void * pToPrint);
	void print_str(char const * pFmt, void * pToPrint);
	void print_float(char const * pFmt, void * pToPrint);
	void print_double(char const * pFmt, void * pToPrint);
	void print_ptr(char const * pFmt, void * pToPrint);
	void print_now(void);

	Field m_fields[N_FIELDS];
	uint8_t m_num_fields = 0;
	print_function m_pfn_printer = NULL;
	char const * m_prefix;

};

#endif