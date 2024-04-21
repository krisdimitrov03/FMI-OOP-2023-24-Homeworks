// Taken from https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2006/Bitsets/DynamicSet

#include "../../include/utils/DynamicSet.h"

using utils::DynamicSet;

DynamicSet::DynamicSet(unsigned N)
{
	bucketsCount = N / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->N = N;
}

void DynamicSet::free()
{
	delete[] buckets;
	bucketsCount = 0;
	buckets = nullptr;
}
void DynamicSet::copyFrom(const DynamicSet& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	N = other.N;
}

DynamicSet::DynamicSet(const DynamicSet& other)
{
	copyFrom(other);
}
DynamicSet& DynamicSet::operator=(const DynamicSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
DynamicSet::~DynamicSet()
{
	free();
}

unsigned DynamicSet::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

void DynamicSet::add(unsigned num)
{
	if (num > N)
		return;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;
	buckets[bucketIndex] |= mask;

	size++;
}

void DynamicSet::remove(unsigned num)
{

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask;
}

bool DynamicSet::contains(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}

unsigned utils::DynamicSet::length() const
{
	return size;
}

void DynamicSet::print() const
{
	std::cout << '{';
	for (int i = 0; i <= N; i++)
	{
		if (contains(i))
			std::cout << i << " ";
	}

	std::cout << '}' << std::endl;
}