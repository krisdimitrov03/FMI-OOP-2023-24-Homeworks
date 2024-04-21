#include "../include/Row.h"
#include <iostream>

void Row::addCell(const char* content, bool isHeader)
{
	if (content == nullptr)
		return;

	cells[size++].setData(content);
	cells[size - 1].isHeader = isHeader;
}

void Row::clear()
{
	for (unsigned i = 0; i < size; i++)
		cells[i].clear();
	size = 0;
}

void Row::print(unsigned printSize, const unsigned* cellsPrintSizes) const
{
	for (unsigned i = 0; i < printSize; i++)
		cells[i].print(cellsPrintSizes[i], i == printSize - 1);

	std::cout << std::endl;
}

void Row::writeTo(std::ofstream& ofs) const
{
	ofs << "\t<tr>\n";

	for (size_t i = 0; i < size; i++)
		cells[i].writeTo(ofs);

	ofs << "\t</tr>\n";
}