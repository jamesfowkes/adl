/* C/C++ Includes */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/* Module Includes */

#include "csvlog.h"

/* Defines, constants, typedefs */

typedef struct _field
{
	void * pFieldValue;
	eCSVDataType eType;
	char const * pFormatter;
} Field;

/* Local Variables */

static Field sFields[N_FIELDS];
static uint8_t sNumFields = 0;

static print_function spfn_printer = NULL;

/* Private Module Functions */

static void print_char(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "c", *(char*)pToPrint);
}

static void print_u8(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIu8, *(uint8_t*)pToPrint);
}

static void print_u16(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIu16, *(uint16_t*)pToPrint);
}

static void print_u32(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIu32, *(uint32_t*)pToPrint);
}

static void print_u64(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIu64, *(uint64_t*)pToPrint);
}

static void print_s8(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIi8, *(int8_t*)pToPrint);
}

static void print_s16(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIi16, *(int16_t*)pToPrint);
}

static void print_s32(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIi32, *(int32_t*)pToPrint);
}

static void print_s64(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%" PRIi64, *(int64_t*)pToPrint);
}

static void print_str(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%s", (char*)pToPrint);
}

static void print_float(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%f", (double)(*(float*)pToPrint));
}

static void print_double(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%f", *(double*)pToPrint);
}

static void print_ptr(char const * pFmt, void * pToPrint)
{
	spfn_printer(pFmt ? pFmt : "%p", pToPrint);
}	

static void print_now()
{
	for (uint8_t i=0; i<sNumFields; i++)
	{
		switch(sFields[i].eType)
		{
		case eCSVDataType_char:
			print_char(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_u8:
			print_u8(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_u16:
			print_u16(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_u32:
			print_u32(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_u64:
			print_u64(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_s8:
			print_s8(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_s16:
			print_s16(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_s32:
			print_s32(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_s64:
			print_s64(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_str:
			print_str(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_float:
			print_float(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_double:
			print_double(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		case eCSVDataType_ptr:
			print_ptr(sFields[i].pFormatter, sFields[i].pFieldValue);
			break;
		default:
			spfn_printer("TYPE?");
			break;
		}

		if (i < (sNumFields-1))
		{
			spfn_printer(",");
		}	
	}
	if (sNumFields)
	{
		spfn_printer("\n");
	}
}

/* Public Functions */

void CSVLog_Init(print_function pfn_printer)
{
	spfn_printer = pfn_printer;

	for (uint8_t i=0; i<N_FIELDS; i++)
	{
		sFields[i].pFieldValue = NULL;
		sFields[i].pFormatter = NULL;
	}
	sNumFields = 0;
}

void CSVLog_AddField(void * pFieldValue, eCSVDataType CSVDataType, char const * pFormatter)
{
	if (sNumFields < (N_FIELDS-1))
	{
		sFields[sNumFields].pFieldValue = pFieldValue;
		sFields[sNumFields].eType = CSVDataType;	
		sFields[sNumFields].pFormatter = pFormatter;	
		sNumFields++;
	}
}

void CSVLog_PrintNow()
{
	if (spfn_printer)
	{
		print_now();
	}	
}
