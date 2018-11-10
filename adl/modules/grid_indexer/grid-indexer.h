#ifndef _GRID_INDEXER_H_
#define _GRID_INDEXER_H_

class GridIndexer
{
public:
	GridIndexer(uint8_t length);
	uint8_t get(uint8_t index);

private:
	uint8_t m_length;
};

#endif