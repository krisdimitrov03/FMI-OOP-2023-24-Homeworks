#pragma once

struct ParsingState {
	bool inTable = false;
	bool inRow = false;
	bool inHeader = false;
	bool inCell = false;

	bool isFormatValid = true;
	bool isTableSizeValid = true;
};