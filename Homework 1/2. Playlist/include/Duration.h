#pragma once

struct Duration {
	unsigned hours;
	unsigned minutes;
	unsigned seconds;

	void print() const;

	unsigned getTotalSeconds() const;
};