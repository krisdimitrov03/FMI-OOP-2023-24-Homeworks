#pragma once

#include "Table.h"

namespace {
	const char ADD_ROW[] = "add-row";
	const char REMOVE_ROW[] = "remove-row";
	const char ADD_CELL[] = "add-cell";
	const char ADD_EMPTY_CELL[] = "add-empty-cell";
	const char EDIT_CELL[] = "edit-cell";
	const char CHANGE_HEADER[] = "change-header";
	const char HELP[] = "help";
	const char PRINT[] = "print";
	const char EXIT[] = "exit";
}

class HtmlParser {
private:
	Table table;

	void fillValuesMatrix(const char* src, char**& dest, size_t size) const;
	void printHelp() const;

	void handleAddRow();
	void handleRemoveRow();
	void handleAddCell();
	void handleAddEmptyCell();
	void handleEditCell();
	void handleChangeHeader();
	void handlePrint() const;
	void handleExit(const char* fileName) const;

public:
	void run();
};