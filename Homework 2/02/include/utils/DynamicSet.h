// Taken from https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2006/Bitsets/DynamicSet

#pragma once
#include <iostream>

namespace utils {

	class DynamicSet
	{
		uint8_t* buckets = nullptr;
		unsigned bucketsCount = 0;
		unsigned N = 0;
		const unsigned elementsInBucket = sizeof(uint8_t) * 8;

		unsigned size = 0;

		void free();
		void copyFrom(const DynamicSet& other);

		unsigned getBucketIndex(unsigned num) const;
	public:
		DynamicSet(unsigned n);

		DynamicSet(const DynamicSet& other);
		DynamicSet& operator=(const DynamicSet& other);
		~DynamicSet();

		void add(unsigned num);
		void remove(unsigned num);
		bool contains(unsigned num) const;
		unsigned length() const;
		void print() const;
	};

}
