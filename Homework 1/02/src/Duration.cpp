#include "../include/Duration.h"
#include <iostream>

void Duration::print() const
{
	if (hours <= 9)
		std::cout << 0;

	std::cout << hours;
	std::cout << ":";

	if (minutes <= 9)
		std::cout << 0;

	std::cout << minutes;
	std::cout << ":";

	if (seconds <= 9)
		std::cout << 0;

	std::cout << seconds;
}

unsigned Duration::getTotalSeconds() const
{
	return seconds + minutes * 60 + hours * 3600;
}
