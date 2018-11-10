/* C/C++ Includes */

#include <stdint.h>
#include <stdlib.h>

/* ADL Includes */

#include "adl.h"
#include "adl-util-grid-indexing.h"

GridIndexer::GridIndexer(uint8_t length) : 
	m_length(length)
{

}

uint8_t GridIndexer::get(uint8_t index)
{
	if (m_length == 1) { return index; }

	uint8_t row = index / m_length;
	uint8_t new_index = index;
	uint8_t row_start;

	if (row & 1)
	{
		row_start = row * m_length;
		new_index = row_start + m_length - (index % m_length) - 1;
	}

	return new_index;

}
