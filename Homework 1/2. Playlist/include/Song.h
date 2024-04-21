#pragma once

#include "Duration.h"
#include <fstream>

typedef char Genre;

namespace globals {
	const int NAME_MAX_LENGTH = 64;
	const int CONTENT_MAX_LENGTH = 256;

	const char JAZZ = 1;
	const char EL = 2;
	const char HIP_HOP = 4;
	const char POP = 8;
	const char ROCK = 16;

	Genre getGenreMask(const char* genres);
	void printGenre(Genre genre);
}

struct Song {
	char name[globals::NAME_MAX_LENGTH + 1] = { '\0' };
	char content[globals::CONTENT_MAX_LENGTH] = { '\0' };
	Genre genre;
	Duration duration;

	void print() const;

	void setGenre(const char* genre);

	void addRythm(unsigned k);

	void mix(const Song& other);

	void save(std::ofstream& ofs) const;
};