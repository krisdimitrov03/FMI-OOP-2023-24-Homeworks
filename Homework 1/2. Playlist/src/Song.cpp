#include "../include/Song.h"
#include <iostream>

void Song::print() const
{
	std::cout << name << ", ";

	duration.print();
	std::cout << ", ";

	globals::printGenre(genre);

	std::cout << std::endl;
}

void Song::setGenre(const char* genre)
{
	if (!genre)
		return;

	this->genre = globals::getGenreMask(genre);
}

void Song::addRythm(unsigned k)
{
	int size = strlen(content);

	if (size == 0 || k >= size * 8)
		return;

	int bucketIdx = size - 1;
	int currentBitIdx = (size * 8) - 1;
	unsigned count = 1;

	while (currentBitIdx > -1) {
		if (count % k == 0) {
			int shiftCount = (size * 8) - currentBitIdx - 1 - (size - bucketIdx - 1) * 8;

			content[bucketIdx] |= (1 << shiftCount);
		}

		currentBitIdx--;

		if (count == 3)
			count = 1;
		else
			count++;

		if (currentBitIdx < (bucketIdx * 8)) {
			bucketIdx--;
		}
	}
}

void Song::mix(const Song& other)
{
	size_t mixSize = std::min(strlen(content), strlen(other.content));

	for (size_t i = 0; i < mixSize; i++)
		content[i] ^= other.content[i];
}

void Song::save(std::ofstream& ofs) const
{
	size_t contentSize = strlen(content);
	ofs.write(content, contentSize * sizeof(char));
}

Genre globals::getGenreMask(const char* genres)
{
	size_t length = strlen(genres);

	Genre result = '\0';

	for (size_t i = 0; i < length; i++) {
		switch (genres[i]) {
		case 'r':
			result |= globals::ROCK;
			break;
		case 'p':
			result |= globals::POP;
			break;
		case 'h':
			result |= globals::HIP_HOP;
			break;
		case 'e':
			result |= globals::EL;
			break;
		case 'j':
			result |= globals::JAZZ;
			break;
		}
	}

	return result;
}

void globals::printGenre(Genre genre)
{
	bool hasAtLeastOne = false;

	if ((ROCK & genre) == ROCK) {
		hasAtLeastOne = true;

		std::cout << "Rock";
	}

	if ((POP & genre) == POP) {
		if (hasAtLeastOne)
			std::cout << "&";

		std::cout << "Pop";
	}

	if ((HIP_HOP & genre) == HIP_HOP) {
		if (hasAtLeastOne)
			std::cout << "&";

		std::cout << "Hip-Hop";
	}

	if ((EL & genre) == EL) {
		if (hasAtLeastOne)
			std::cout << "&";

		std::cout << "Electro-Music";
	}

	if ((JAZZ & genre) == JAZZ) {
		if (hasAtLeastOne)
			std::cout << "&";

		std::cout << "Jazz";
	}
}
