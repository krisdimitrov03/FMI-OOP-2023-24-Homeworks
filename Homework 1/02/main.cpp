#include <iostream>
#include <fstream>
#include "./include/Playlist.h"

int main()
{
	Playlist p;
	p.add("Song 2", 0, 1, 55, "rp", "song2.dat");
	p.add("Song 1", 0, 1, 5, "p", "song1.dat");

	p.print();

	p.sortByName();
	p.print();

	const Song* song = p.findByName("Song 1");
	if (song)
		song->print();

	Song* songs = nullptr;
	size_t size = 0;

	p.findByGenre('p', songs, size);
	for (size_t i = 0; i < size; i++)
		songs[i].print();

	delete[] songs;
	songs = nullptr;

	p.findByGenre('r', songs, size);

	for (size_t i = 0; i < size; i++)
		songs[i].print();

	delete[] songs;
	songs = nullptr;

	p.mix("Song 1", "Song 2");
	p.save("Song 1", "song3.dat");
}