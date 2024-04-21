#include "../include/HtmlParser.h"
#include <iostream>

namespace {
	const int ADD_ROW_MAX_INPUT_SIZE = 770;

	size_t getCharCount(const char* str, char ch) {
		size_t size = strlen(str);

		size_t res = 0;

		for (size_t i = 0; i < size; i++)
			if (str[i] == ch)
				res++;

		return res;
	}

	void deleteCharMatrix(char** arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			if (!arr[i])
				delete[] arr[i];

		delete[] arr;
	}
}

void HtmlParser::run()
{
	std::cout << "Enter fileName to load table from:" << std::endl;

	char fileName[100];
	std::cin >> fileName;

	LoadResult loadResult = table.loadFromFile(fileName);

	switch (loadResult) {
	case LoadResult::NullPtrFileName:
		std::cout << "File name is nullptr";
		return;
	case LoadResult::FileOpenFailed:
		std::cout << "File could not be open";
		return;
	case LoadResult::IncorrectTableFormat:
		std::cout << "Incorrect table format";
		return;
	case LoadResult::TableSizeOverflow:
		std::cout << "Table size too large to be loaded";
		return;
	case LoadResult::OK:
		std::cout << "Table loaded from " << fileName << std::endl;
		break;
	}

	while (true) {
		std::cout << "Enter command:" << std::endl;

		char command[100] = { '\0' };
		std::cin >> command;

		if (globals::equals(command, ADD_ROW)) {
			handleAddRow();
		}
		else if (globals::equals(command, REMOVE_ROW)) {
			handleRemoveRow();
		}
		else if (globals::equals(command, ADD_CELL)) {
			handleAddCell();
		}
		else if (globals::equals(command, ADD_EMPTY_CELL)) {
			handleAddEmptyCell();
		}
		else if (globals::equals(command, EDIT_CELL)) {
			handleEditCell();
		}
		else if (globals::equals(command, CHANGE_HEADER)) {
			handleChangeHeader();
		}
		else if (globals::equals(command, PRINT)) {
			handlePrint();
		}
		else if (globals::equals(command, HELP)) {
			printHelp();
		}
		else if (globals::equals(command, EXIT)) {
			handleExit(fileName);
			return;
		}
		else {
			std::cout << "Unknown command" << std::endl;
		}

		std::cout << std::endl;
	}
}

void HtmlParser::fillValuesMatrix(const char* src, char**& dest, size_t size) const
{
	dest = new char* [size];

	for (size_t i = 0, valueIdx = 0; i < ADD_ROW_MAX_INPUT_SIZE && valueIdx < size; i++) {
		if (i == 0 && src[i] == ' ')
			i++;

		if (src[i] == '\0')
			break;

		size_t contentSize = 0;
		char buff[globals::MAX_CELL_LENGTH] = { '\0' };

		while (src[i] != '|' && contentSize < globals::MAX_CELL_LENGTH
			&& i < ADD_ROW_MAX_INPUT_SIZE) {
			if (src[i] == '\0')
				break;

			buff[contentSize++] = src[i++];
		}

		dest[valueIdx] = new char[contentSize];
		strcpy(dest[valueIdx], buff);

		while (src[i] != '|' && i < ADD_ROW_MAX_INPUT_SIZE) {
			if (src[i] == '\0')
				break;
			i++;
		}

		contentSize = 0;
		valueIdx++;
	}
}

void HtmlParser::printHelp() const
{
	std::cout << "add-row <rowNum> <value1>|<value2>|<value3>|...." << std::endl;
	std::cout << "remove-row <rowNum>" << std::endl;
	std::cout << "add-cell <rowNum> <isHeader> <value>" << std::endl;
	std::cout << "add-empty-cell <rowNum>" << std::endl;
	std::cout << "edit-cell <rowNum> <colNum> <newValue>" << std::endl;
	std::cout << "change-header <rowNum> <colNum> <isHeader>" << std::endl;
	std::cout << "print" << std::endl;
	std::cout << "exit" << std::endl;
	std::cout << "help" << std::endl;
}

void HtmlParser::handleAddRow()
{
	int number;
	std::cin >> number;

	char input[ADD_ROW_MAX_INPUT_SIZE] = { '\0' };
	std::cin.getline(input, ADD_ROW_MAX_INPUT_SIZE, '\n');

	char** values = nullptr;
	size_t size = getCharCount(input, '|') + 1;

	fillValuesMatrix(input, values, size);

	CRUDResult result = table.addRow(number, (const char**)values, size);

	if (result == CRUDResult::OK)
		std::cout << "Row added" << std::endl;
	else
		std::cout << "There was a problem adding row" << std::endl;

	deleteCharMatrix(values, size);
}

void HtmlParser::handleRemoveRow()
{
	int number;
	std::cin >> number;

	CRUDResult result = table.removeRow(number);

	if (result == CRUDResult::OK)
		std::cout << "Row " << number << " removed" << std::endl;
	else
		std::cout << "Invalid row number" << std::endl;
}

void HtmlParser::handleAddCell()
{
	int rowNum;
	bool isHeader;
	char value[globals::MAX_CELL_LENGTH] = { '\0' };

	std::cin >> rowNum >> isHeader;
	std::cin.getline(value, globals::MAX_CELL_LENGTH, '\n');

	CRUDResult result = table.addCell(rowNum, value, isHeader);

	if (result == CRUDResult::OK)
		std::cout << "Cell added to row " << rowNum << std::endl;
	else
		std::cout << "There was a problem adding cell" << std::endl;
}

void HtmlParser::handleAddEmptyCell()
{
	int rowNum;

	std::cin >> rowNum;

	CRUDResult result = table.addEmptyCell(rowNum);

	if (result == CRUDResult::OK)
		std::cout << "Cell added to row " << rowNum << std::endl;
	else
		std::cout << "There was a problem adding cell" << std::endl;
}

void HtmlParser::handleEditCell()
{
	int rowNum, colNum;
	std::cin >> rowNum >> colNum;

	char newValue[globals::MAX_CELL_LENGTH];
	std::cin.getline(newValue, globals::MAX_CELL_LENGTH, '\n');

	char* ptr = newValue;

	CRUDResult result = table.editCell(rowNum, colNum, ++ptr);

	if (result == CRUDResult::OK)
		std::cout << "Cell changes saved" << std::endl;
	else
		std::cout << "There was a problem editing" << std::endl;
}

void HtmlParser::handleChangeHeader()
{
	int row, col;
	bool isHeader;
	std::cin >> row >> col >> isHeader;

	CRUDResult result = table.changeHeader(row, col, isHeader);

	if (result == CRUDResult::OK)
		std::cout << "Cell changes saved" << std::endl;
	else
		std::cout << "There was a problem saving changes" << std::endl;
}

void HtmlParser::handlePrint() const
{
	table.print();
}

void HtmlParser::handleExit(const char* fileName) const
{
	SaveResult result = table.saveToFile(fileName);

	if (result != SaveResult::OK)
		std::cout << "There was a problem saving the table in "
		<< fileName << std::endl;

	return;
}
