#pragma once

#include <fstream>

#pragma warning (disable : 4996)

namespace globals {
	const int MAX_CELL_LENGTH = 50;
}

struct Cell {
	char data[globals::MAX_CELL_LENGTH + 1] = { '\0' };
	bool isHeader = false;
	unsigned size = 0;

	void setData(const char* content);
	void clear();

	void print(unsigned printSize, bool isLast) const;
	void writeTo(std::ofstream& ofs) const;
};