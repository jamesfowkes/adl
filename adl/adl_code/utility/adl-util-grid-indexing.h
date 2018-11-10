#ifndef _ADL_UTIL_GRID_INDEXING_H_
#define _ADL_UTIL_GRID_INDEXING_H_

class GridIndexer
{
public:
	GridIndexer(uint8_t length);
	uint8_t get(uint8_t index);

private:
	uint8_t m_length;
};

#endif