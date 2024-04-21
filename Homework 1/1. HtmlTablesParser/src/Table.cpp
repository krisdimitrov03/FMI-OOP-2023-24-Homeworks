#include "../include/Table.h"

namespace {
	const int BUFF_SIZE = 1024;

	const char TAG_OPENING_SYMBOL = '<';
	const char TAG_CLOSING_SYMBOL = '>';

	const char TABLE_OPENING_TAG[] = "table";
	const char TABLE_CLOSING_TAG[] = "/table";

	const char ROW_OPENING_TAG[] = "tr";
	const char ROW_CLOSING_TAG[] = "/tr";

	const char HEADER_OPENING_TAG[] = "th";
	const char HEADER_CLOSING_TAG[] = "/th";

	const char CELL_OPENING_TAG[] = "td";
	const char CELL_CLOSING_TAG[] = "/td";

	bool isDigit(char ch) {
		return ch >= '0' && ch <= '9';
	}

	void handleCharEntityReferences(const char* src, char*& dest) {
		size_t length = strlen(src);
		size_t destLength = 0;

		for (size_t i = 0; i < length; i++)
		{
			if (i == length)
				break;

			if (i + 2 < length && src[i] == '&' && src[i + 1] == '#') {
				if (isDigit(src[i + 2])) {
					unsigned charValue = 0;
					i += 2;

					while (i < length && isDigit(src[i])) {
						charValue *= 10;
						charValue += src[i] - '0';
						i++;
					}

					if (charValue > 255)
						return;

					dest[destLength++] = charValue;
					i--;
				}
				else {
					dest[destLength++] = src[i++];
					dest[destLength++] = src[i];
				}
			}
			else {
				dest[destLength++] = src[i];
			}
		}
	}
}

bool globals::equals(const char* lhs, const char* rhs) {
	return strcmp(lhs, rhs) == 0;
}

int Table::parse(std::ifstream& ifs)
{
	ParsingState state;

	unsigned maxRowLen = 0;
	unsigned maxCellLens[globals::MAX_CELLS_COUNT] = { 0 };

	char current = ifs.get();

	while (current != TAG_OPENING_SYMBOL) {
		if (ifs.eof())
			return -1;

		current = ifs.get();
	}

	while (!ifs.eof()) {
		if (current == TAG_OPENING_SYMBOL) {
			if (!handleTagOpeningSymbol(ifs, state, current))
				break;
		}
		else {
			if (!handleTagClosingSymbol(ifs, state, current))
				break;
		}
	}

	if (!state.isFormatValid)
		return -1;
	else if (!state.isTableSizeValid)
		return -2;
	else
		return 0;
}

bool Table::handleTagOpeningSymbol(std::ifstream& ifs, ParsingState& state, char& current)
{
	char buff[BUFF_SIZE];
	ifs.getline(buff, BUFF_SIZE, TAG_CLOSING_SYMBOL);
	current = TAG_CLOSING_SYMBOL;

	handleTags(state, buff);

	if (!state.isFormatValid)
		return false;

	if (!state.isTableSizeValid)
		return false;

	if (!state.inTable) {
		if (state.inRow || state.inCell || state.inHeader)
			state.isFormatValid = false;

		return false;
	}

	return true;
}

bool Table::handleTagClosingSymbol(std::ifstream& ifs, ParsingState& state, char& current)
{
	if (!state.inHeader && !state.inCell) {
		while (current != TAG_OPENING_SYMBOL)
			current = ifs.get();
	}
	else {
		char buff[BUFF_SIZE] = { '\0' };
		ifs.getline(buff, BUFF_SIZE, TAG_OPENING_SYMBOL);
		current = TAG_OPENING_SYMBOL;

		char cellContent[BUFF_SIZE] = { '\0' };
		char* ptr = cellContent;
		handleCharEntityReferences(buff, ptr);

		if (strlen(cellContent) >= globals::MAX_CELL_LENGTH) {
			state.isTableSizeValid = false;
			return false;
		}

		rows[size].addCell(ptr, state.inHeader);

		return true;
	}
}

void Table::handleTags(ParsingState& state, const char* buff)
{
	if (globals::equals(buff, TABLE_OPENING_TAG) || globals::equals(buff, TABLE_CLOSING_TAG))
		handleTableTags(state, buff);
	else if (globals::equals(buff, ROW_OPENING_TAG) || globals::equals(buff, ROW_CLOSING_TAG))
		handleRowTags(state, buff);
	else if (globals::equals(buff, HEADER_OPENING_TAG) || globals::equals(buff, HEADER_CLOSING_TAG))
		handleHeaderTags(state, buff);
	else if (globals::equals(buff, CELL_OPENING_TAG) || globals::equals(buff, CELL_CLOSING_TAG))
		handleCellTags(state, buff);
	else
		state.isFormatValid = false;
}

void Table::handleTableTags(ParsingState& state, const char* buff)
{
	if (globals::equals(buff, TABLE_OPENING_TAG)) {
		if (state.inTable) {
			state.isFormatValid = false;
			return;
		}

		state.inTable = true;
	}
	else {
		if (!state.inTable) {
			state.isFormatValid = false;
			return;
		}

		state.inTable = false;
	}
}

void Table::handleRowTags(ParsingState& state, const char* buff)
{
	if (globals::equals(buff, ROW_OPENING_TAG)) {
		if (!state.inTable || state.inRow) {
			state.isFormatValid = false;
			return;
		}

		if (size == globals::MAX_ROWS_COUNT - 1) {
			state.isTableSizeValid = false;
			return;
		}

		state.inRow = true;
	}
	else {
		if (!state.inRow) {
			state.isFormatValid = false;
			return;
		}

		state.inRow = false;
		size++;
	}
}

void Table::handleHeaderTags(ParsingState& state, const char* buff)
{
	if (globals::equals(buff, HEADER_OPENING_TAG)) {
		if (!state.inTable || !state.inRow || state.inHeader || state.inCell) {
			state.isFormatValid = false;
			return;
		}

		if (rows[size].size == globals::MAX_CELLS_COUNT) {
			state.isTableSizeValid = false;
			return;
		}

		state.inHeader = true;
	}
	else {
		if (!state.inHeader) {
			state.isFormatValid = false;
			return;
		}

		state.inHeader = false;
	}
}

void Table::handleCellTags(ParsingState& state, const char* buff)
{
	if (globals::equals(buff, CELL_OPENING_TAG)) {
		if (!state.inTable || !state.inRow || state.inHeader || state.inCell) {
			state.isFormatValid = false;
			return;
		}

		if (rows[size].size == globals::MAX_CELLS_COUNT) {
			state.isTableSizeValid = false;
			return;
		}

		state.inCell = true;
	}
	else {
		if (!state.inCell) {
			state.isFormatValid = false;
			return;
		}

		state.inCell = false;
	}
}

LoadResult Table::loadFromFile(const char* fileName)
{
	if (!fileName)
		return LoadResult::NullPtrFileName;

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		return LoadResult::FileOpenFailed;

	int parseResult = parse(ifs);

	ifs.close();

	if (parseResult == -1)
		return LoadResult::IncorrectTableFormat;
	else if (parseResult == -2)
		return LoadResult::TableSizeOverflow;
	else
		return LoadResult::OK;
}

CRUDResult Table::addRow(unsigned number, const char** values, unsigned valuesCount)
{
	if (!values)
		return CRUDResult::NullPtr;

	if (number == 0)
		return CRUDResult::InvalidParameter;

	unsigned idx = number - 1;

	if (idx >= globals::MAX_ROWS_COUNT || valuesCount >= globals::MAX_CELLS_COUNT)
		return CRUDResult::InvalidParameter;

	if (size == globals::MAX_ROWS_COUNT - 1)
		return CRUDResult::NoSpace;

	for (unsigned i = size - 1; i >= idx; i--)
		rows[i + 1] = rows[i];

	rows[idx].clear();

	for (unsigned i = 0; i < valuesCount; i++)
		rows[idx].addCell(values[i], false);

	size++;

	return CRUDResult::OK;
}

CRUDResult Table::removeRow(unsigned number)
{
	if (number == 0)
		return CRUDResult::InvalidParameter;

	unsigned idx = number - 1;

	if (idx >= size)
		return CRUDResult::InvalidParameter;

	for (unsigned i = idx + 1; i < size; i++)
		rows[i - 1] = rows[i];

	size--;

	return CRUDResult::OK;
}

CRUDResult Table::addCell(unsigned row, const char* value, bool isHeader)
{
	if (!value)
		return CRUDResult::NullPtr;

	if (row == 0 || strlen(value) > globals::MAX_CELL_LENGTH)
		return CRUDResult::InvalidParameter;

	unsigned idx = row - 1;

	if (idx >= size)
		return CRUDResult::InvalidParameter;

	if (size == globals::MAX_CELLS_COUNT - 1)
		return CRUDResult::NoSpace;

	rows[idx].addCell(value, isHeader);

	return CRUDResult::OK;
}

CRUDResult Table::addEmptyCell(unsigned row)
{
	return addCell(row, "", false);
}

CRUDResult Table::editCell(unsigned row, unsigned col, const char* newValue)
{
	if (!newValue)
		return CRUDResult::NullPtr;

	if (row == 0 || col == 0)
		return CRUDResult::InvalidParameter;

	unsigned rowIdx = row - 1;
	unsigned colIdx = col - 1;

	if (rowIdx >= size || colIdx >= rows[rowIdx].size
		|| strlen(newValue) > globals::MAX_CELL_LENGTH)
		return CRUDResult::InvalidParameter;

	rows[rowIdx].cells[colIdx].setData(newValue);

	return CRUDResult::OK;
}

CRUDResult Table::changeHeader(unsigned row, unsigned col, bool isHeader)
{
	if (row == 0 || col == 0)
		return CRUDResult::InvalidParameter;

	unsigned rowIdx = row - 1;
	unsigned colIdx = col - 1;

	if (rowIdx >= size || colIdx >= rows[rowIdx].size)
		return CRUDResult::InvalidParameter;

	rows[rowIdx].cells[colIdx].isHeader = isHeader;

	return CRUDResult::OK;
}

void Table::print() const
{
	unsigned cellsPrintSizes[globals::MAX_CELLS_COUNT] = { 0 };
	unsigned rowsPrintSize = 0;

	//handle row padding
	for (unsigned i = 0; i < size; i++)
		if (rows[i].size > rowsPrintSize)
			rowsPrintSize = rows[i].size;

	//handle cell padding
	for (unsigned i = 0; i < size; i++) {
		for (int j = 0; j < rowsPrintSize; j++) {
			unsigned currentSize = rows[i].cells[j].isHeader
				? rows[i].cells[j].size + 2
				: rows[i].cells[j].size;

			if (currentSize > cellsPrintSizes[j])
				cellsPrintSizes[j] = currentSize;
		}
	}

	//print
	for (unsigned i = 0; i < size; i++)
		rows[i].print(rowsPrintSize, cellsPrintSizes);
}

SaveResult Table::saveToFile(const char* fileName) const
{
	if (!fileName)
		return SaveResult::NullPtr;

	std::ofstream ofs(fileName);

	if (!ofs.is_open())
		return SaveResult::FileOpenFailed;

	ofs << "<table>\n";

	for (size_t i = 0; i < size; i++)
		rows[i].writeTo(ofs);

	ofs << "</table>\n";

	return SaveResult::OK;
}