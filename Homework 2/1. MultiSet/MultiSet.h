#pragma once
#include <cstdint>

class MultiSet {
private:
	static constexpr short BUCKET_SIZE = sizeof(uint8_t);

public:
	MultiSet(int n, int k);

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	MultiSet(MultiSet&& other) noexcept;
	MultiSet& operator=(MultiSet&& other) noexcept;
	~MultiSet();

	void add(int num);

	int count(int num) const;

	void print() const;

	void printInMemory() const;

	void load(const char* fileName);

	void save(const char* fileName) const;

	MultiSet getIntersection(const MultiSet& other) const;

	MultiSet getDifference(const MultiSet& other) const;

	MultiSet getComplement() const;


private:
	uint8_t* _buckets;
	int _size;

	int _n;
	int _k;
	int _maxCountOfNum;

	void free();
	void copyFrom(const MultiSet& other);
	void moveFrom(MultiSet&& other) noexcept;

	int getBucketsCount(int n, int k) const;
	int readCountFromBucket(int bitIndex) const;
	void replace(int bitIndex, int value);
};
