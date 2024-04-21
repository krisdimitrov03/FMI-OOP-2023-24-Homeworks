#pragma once

#include "Row.h"
#include "ParsingState.h"
#include "LoadResult.h"
#include "CRUDResult.h"
#include "SaveResult.h"

#pragma warning (disable : 4996)

namespace globals {
	const int MAX_ROWS_COUNT = 100;

	bool equals(const char* lhs, const char* rhs);
}

class Table {
private:
	Row rows[globals::MAX_ROWS_COUNT];
	unsigned size = 0;

	int parse(std::ifstream& ifs);
	bool handleTagOpeningSymbol(std::ifstream& ifs, ParsingState& state, char& current);
	bool handleTagClosingSymbol(std::ifstream& ifs, ParsingState& state, char& current);
	void handleTags(ParsingState& state, const char* buff);
	void handleTableTags(ParsingState& state, const char* buff);
	void handleRowTags(ParsingState& state, const char* buff);
	void handleHeaderTags(ParsingState& state, const char* buff);
	void handleCellTags(ParsingState& state, const char* buff);

public:
	LoadResult loadFromFile(const char* fileName);
	CRUDResult addRow(unsigned number, const char** values, unsigned valuesCount);
	CRUDResult removeRow(unsigned number);
	CRUDResult addCell(unsigned row, const char* value, bool isHeader);
	CRUDResult addEmptyCell(unsigned row);
	CRUDResult editCell(unsigned row, unsigned col, const char* newValue);
	CRUDResult changeHeader(unsigned row, unsigned col, bool isHeader);
	void print() const;
	SaveResult saveToFile(const char* fileName) const;
};