#include "MultiSet.h"
#include <exception>
#include <iostream>
#include <fstream>

MultiSet::MultiSet(int n, int k) : _n(n), _k(k), _maxCountOfNum((1 << k) - 1), _size(getBucketsCount(n, k)) {
	_buckets = new uint8_t[_size]();
}

void MultiSet::free() {
	delete[] _buckets;
	_buckets = nullptr;
}

void MultiSet::copyFrom(const MultiSet& other) {
	_n = other._n;
	_k = other._k;
	_maxCountOfNum = other._maxCountOfNum;

	_size = other._size;
	_buckets = new uint8_t[_size]();
	for (size_t i = 0; i < _size; i++)
		_buckets[i] = other._buckets[i];
}

void MultiSet::moveFrom(MultiSet&& other) noexcept {
	_buckets = other._buckets;
	_n = other._n;
	_k = other._k;
	_maxCountOfNum = other._maxCountOfNum;
	_size = other._size;

	other._buckets = nullptr;
	other._n = 0;
	other._k = 0;
	other._maxCountOfNum = 0;
	other._size = 0;
}

MultiSet::~MultiSet() {
	free();
}

MultiSet::MultiSet(const MultiSet& other) {
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return (*this);
}

MultiSet::MultiSet(MultiSet&& other) noexcept {
	moveFrom(std::move(other));
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return (*this);
}

void MultiSet::add(int num) {
	if (num < 0 || num > _n)
		throw std::exception("number out of range");

	int bitIndex = num * _k;
	int count = readCountFromBucket(bitIndex);

	if (count >= _maxCountOfNum)
		throw std::exception("max count of num exceeded");

	replace(bitIndex, count + 1);
}

int MultiSet::count(int num) const {
	if (num < 0 || num > _n)
		return 0;

	return readCountFromBucket(num * _k);
}

void MultiSet::print() const {
	std::cout << "{ ";

	for (int i = 0; i <= _n; i++) {
		int numCount = count(i);

		for (size_t j = 0; j < numCount; j++) {
			std::cout << i;

			if (!(i == _n && j == numCount - 1)) {
				std::cout << " ";
			}
		}
	}

	std::cout << "}";
}

void MultiSet::printInMemory() const {
	std::cout << "|";

	for (int i = 0; i < _size; i++) {
		for (int j = BUCKET_SIZE - 1; j >= 0; j--)
			std::cout << ((_buckets[i] >> j) & 1);
		std::cout << "|";
	}

	std::cout << std::endl;
}

void MultiSet::save(const char* fileName) const {
	if (!fileName)
		throw std::exception("fileName is nullptr");

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		throw std::exception("file could not be open");

	ofs.write((char*)&_n, sizeof(int));
	ofs.write((char*)&_k, sizeof(int));

	for (size_t i = 0; i < _size; i++)
		ofs.write((const char*)&_buckets[i], sizeof(uint8_t));

	ofs.close();
}

void MultiSet::load(const char* fileName) {
	if (!fileName)
		throw std::exception("fileName is nullptr");

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
		throw std::exception("file could not be open");

	int n = 0, k = 0;

	ifs.read((char*)&n, sizeof(int));
	ifs.read((char*)&k, sizeof(int));

	MultiSet set(n, k);

	for (size_t i = 0; i < set._size; i++)
		ifs.read((char*)&(set._buckets[i]), sizeof(uint8_t));

	ifs.close();

	(*this) = set;
}

MultiSet MultiSet::getIntersection(const MultiSet& other) const {
	MultiSet result(_n, _k);

	for (int i = 0; i <= _n; i++)
	{
		int thisCountOfNum = count(i);
		int otherCountOfNum = other.count(i);

		result.replace(i * _k, std::min(thisCountOfNum, otherCountOfNum));
	}

	return result;
}

MultiSet MultiSet::getDifference(const MultiSet& other) const {
	MultiSet result(_n, _k);

	for (int i = 0; i <= _n; i++)
	{
		int thisCountOfNum = count(i);
		int otherCountOfNum = other.count(i);

		result.replace(i * _k, std::max(0, thisCountOfNum - otherCountOfNum));
	}

	return result;
}

MultiSet MultiSet::getComplement() const {
	MultiSet result(_n, _k);

	for (int i = 0; i <= _n; i++)
	{
		int countOfNum = count(i);
		result.replace(i * _k, _maxCountOfNum - countOfNum);
	}

	return result;
}

int MultiSet::getBucketsCount(int n, int k) const {
	return ((n * k) / BUCKET_SIZE) + 1;
}

int MultiSet::readCountFromBucket(int bitIndex) const {
	int bucketIndex = bitIndex / BUCKET_SIZE;
	int bitIdxInBucket = bitIndex % BUCKET_SIZE;
	int bitsFirst = BUCKET_SIZE - bitIdxInBucket;

	int result = (_buckets[bucketIndex] >> bitIdxInBucket);

	if (bitIdxInBucket + _k > BUCKET_SIZE) {
		result |= (_buckets[bucketIndex + 1] << bitsFirst);
	}

	return result & ((1 << _k) - 1);
}

void MultiSet::replace(int bitIndex, int value) {
	int bucketIndex = bitIndex / BUCKET_SIZE;
	int bitIdxInBucket = bitIndex % BUCKET_SIZE;
	int bitsFirst = BUCKET_SIZE - bitIdxInBucket;

	unsigned char mask = ((1 << _k) - 1) << bitIdxInBucket;

	_buckets[bucketIndex] &= ~mask;
	_buckets[bucketIndex] |= (value << bitIdxInBucket) & mask;

	if (bitIdxInBucket + _k > BUCKET_SIZE) {
		mask = ((1 << _k) - 1) >> bitsFirst;
		_buckets[bucketIndex + 1] &= ~mask;
		_buckets[bucketIndex + 1] |= (value >> bitsFirst) & mask;
	}
}