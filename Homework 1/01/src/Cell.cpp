#include "../include/Cell.h"
#include <iostream>

void Cell::setData(const char* content)
{
	size = strlen(content);
	strcpy(data, content);
}

void Cell::clear()
{
	strcpy(data, "");
	size = 0;
	isHeader = false;
}

void Cell::print(unsigned printSize, bool isLast) const
{
	std::cout << '|';

	if (isHeader)
		std::cout << '*';
	else
		std::cout << ' ';

	if (size != 0)
		std::cout << data;

	unsigned countOfSpaces = printSize - size;

	for (unsigned j = 0; j < countOfSpaces; j++)
		std::cout << ' ';

	if (isHeader)
		std::cout << '*';
	else
		std::cout << ' ';

	if (isLast)
		std::cout << '|';
}

void Cell::writeTo(std::ofstream& ofs) const
{
	if (isHeader)
		ofs << "\t\t<th>";
	else
		ofs << "\t\t<td>";

	ofs << data;

	if (isHeader)
		ofs << "</th>\n";
	else
		ofs << "</td>\n";
}
