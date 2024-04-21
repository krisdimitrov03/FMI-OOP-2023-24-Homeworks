#pragma once

#include "Cell.h"

namespace globals {
	const int MAX_CELLS_COUNT = 15;
}

struct Row {
	Cell cells[globals::MAX_CELLS_COUNT];
	unsigned size = 0;

	void addCell(const char* content, bool isHeader);
	void clear();
	void print(unsigned printSize, const unsigned* cellsPrintSizes) const;
	void writeTo(std::ofstream& ofs) const;
};