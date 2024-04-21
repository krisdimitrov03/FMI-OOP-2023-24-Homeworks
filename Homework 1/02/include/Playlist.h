#pragma once

#include "Song.h"

namespace globals {
	const int MAX_SONGS_COUNT = 30;
}

class Playlist {
private:
	Song songs[globals::MAX_SONGS_COUNT];
	size_t size = 0;

	void sortBy(bool (*pred)(const Song&, const Song&)) const;

public:
	bool add(const char* name,
		unsigned hours,
		unsigned minutes,
		unsigned seconds,
		const char* genre,
		const char* fileName);

	void print() const;

	const Song* findByName(const char* name) const;

	void findByGenre(Genre genre, Song*& dest, size_t& size) const;

	void sortByDuration() const;

	void sortByName() const;

	bool addRythm(const char* songName, unsigned k);

	bool mix(const char* leftSongName, const char* rightSongName);

	bool save(const char* songName, const char* fileName) const;
};