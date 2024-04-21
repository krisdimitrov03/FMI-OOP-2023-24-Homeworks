#include "../include/Playlist.h"
#include <fstream>

#pragma warning (disable : 4996)

namespace {
	bool validateDuration(unsigned hours, unsigned minutes, unsigned seconds) {
		return minutes <= 59 && seconds <= 59;
	}
}

void Playlist::sortBy(bool(*pred)(const Song&, const Song&)) const
{
	for (size_t i = 0; i < size - 1; i++) {
		for (size_t j = 0; j < size - i - 1; j++) {
			if (pred(songs[j], songs[j + 1])) {
				Song temp = songs[j];
				(Song&)(songs[j]) = songs[j + 1];
				(Song&)(songs[j + 1]) = temp;
			}
		}
	}
}

bool Playlist::add(const char* name, unsigned hours, unsigned minutes, unsigned seconds, const char* genre, const char* fileName)
{
	if (!name || !genre || !fileName || !validateDuration(hours, minutes, seconds))
		return false;

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open())
		return false;

	Song& song = songs[size];
	strcpy(song.name, name);
	song.duration = { hours, minutes, seconds };
	song.setGenre(genre);

	file.seekg(0, std::ios::end);
	size_t contentSize = file.tellg();
	file.seekg(0, std::ios::beg);
	file.read(song.content, contentSize * sizeof(char));

	size++;
	file.close();

	return true;
}

void Playlist::print() const
{
	for (size_t i = 0; i < size; i++)
		songs[i].print();
}

const Song* Playlist::findByName(const char* name) const
{
	if (!name)
		return nullptr;

	for (size_t i = 0; i < size; i++)
		if (strcmp(songs[i].name, name) == 0)
			return &(songs[i]);

	return nullptr;
}

void Playlist::findByGenre(Genre genre, Song*& dest, size_t& count) const
{
	char genreStr[2]{ genre };

	char searchedGenre = globals::getGenreMask(genreStr);

	count = 0;

	for (size_t i = 0; i < size; i++)
		if ((searchedGenre & songs[i].genre) == searchedGenre)
			count++;

	dest = new Song[count];

	for (size_t i = 0, resIdx = 0; i < size; i++)
		if ((searchedGenre & songs[i].genre) == searchedGenre)
			dest[resIdx++] = songs[i];
}

void Playlist::sortByDuration() const
{
	sortBy(
		[](const Song& lhs, const Song& rhs) {
			return lhs.duration.getTotalSeconds() > rhs.duration.getTotalSeconds();
		}
	);
}

void Playlist::sortByName() const
{
	sortBy(
		[](const Song& lhs, const Song& rhs) {
			return strcmp(lhs.name, rhs.name) > 0;
		}
	);
}

bool Playlist::addRythm(const char* songName, unsigned k)
{
	Song* songPtr = (Song*)findByName(songName);

	if (!songPtr)
		return false;

	songPtr->addRythm(k);

	return true;
}

bool Playlist::mix(const char* leftSongName, const char* rightSongName)
{
	if (!leftSongName || !rightSongName)
		return false;

	Song* leftPtr = (Song*)findByName(leftSongName);
	Song* rightPtr = (Song*)findByName(rightSongName);

	if (!leftPtr || !rightPtr)
		return false;

	leftPtr->mix(*rightPtr);

	return true;
}

bool Playlist::save(const char* songName, const char* fileName) const
{
	if (!songName || !fileName)
		return false;

	const Song* songPtr = findByName(songName);

	if (!songPtr)
		return false;

	std::ofstream out(fileName, std::ios::binary);

	if (!out.is_open())
		return false;

	songPtr->save(out);

	out.close();

	return true;
}
