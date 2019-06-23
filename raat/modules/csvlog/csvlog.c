/* C/C++ Includes */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/* Module Includes */

#include "csvlog.h"

/* Defines, constants, typedefs */

/* Local Variables */

/* Private Module Functions */

void CSVLog::print_char(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%c", *(char*)pToPrint);
}

void CSVLog::print_u8(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIu8, *(uint8_t*)pToPrint);
}

void CSVLog::print_u16(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIu16, *(uint16_t*)pToPrint);
}

void CSVLog::print_u32(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIu32, *(uint32_t*)pToPrint);
}

void CSVLog::print_u64(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIu64, *(uint64_t*)pToPrint);
}

void CSVLog::print_s8(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIi8, *(int8_t*)pToPrint);
}

void CSVLog::print_s16(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIi16, *(int16_t*)pToPrint);
}

void CSVLog::print_s32(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIi32, *(int32_t*)pToPrint);
}

void CSVLog::print_s64(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%" PRIi64, *(int64_t*)pToPrint);
}

void CSVLog::print_str(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%s", (char*)pToPrint);
}

void CSVLog::print_float(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%f", (double)(*(float*)pToPrint));
}

void CSVLog::print_double(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%f", *(double*)pToPrint);
}

void CSVLog::print_ptr(char const * pFmt, void * pToPrint)
{
	m_pfn_printer(pFmt ? pFmt : "%p", pToPrint);
}	

void CSVLog::print_now()
{
	for (uint8_t i=0; i<m_num_fields; i++)
	{
		switch(m_fields[i].eType)
		{
		case eCSVDataType_char:
			print_char(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_u8:
			print_u8(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_u16:
			print_u16(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_u32:
			print_u32(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_u64:
			print_u64(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_s8:
			print_s8(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_s16:
			print_s16(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_s32:
			print_s32(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_s64:
			print_s64(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_str:
			print_str(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_float:
			print_float(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_double:
			print_double(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		case eCSVDataType_ptr:
			print_ptr(m_fields[i].pFormatter, m_fields[i].pFieldValue);
			break;
		default:
			m_pfn_printer("TYPE?");
			break;
		}

		if (i < (m_num_fields-1))
		{
			m_pfn_printer(",");
		}	
	}
	if (m_num_fields)
	{
		m_pfn_printer("\n");
	}
}

/* Public Functions */

CSVLog::CSVLog(print_function pfn_printer) : m_pfn_printer(pfn_printer)
{
	for (uint8_t i=0; i<N_FIELDS; i++)
	{
		m_fields[i].pFieldValue = NULL;
		m_fields[i].pFormatter = NULL;
	}
	m_num_fields = 0;
}

void CSVLog::AddField(void * pFieldValue, eCSVDataType CSVDataType, char const * pFormatter)
{
	if (m_num_fields < (N_FIELDS-1))
	{
		m_fields[m_num_fields].pFieldValue = pFieldValue;
		m_fields[m_num_fields].eType = CSVDataType;	
		m_fields[m_num_fields].pFormatter = pFormatter;	
		m_num_fields++;
	}
}

void CSVLog::PrintNow()
{
	if (m_pfn_printer)
	{
		this->print_now();
	}	
}
