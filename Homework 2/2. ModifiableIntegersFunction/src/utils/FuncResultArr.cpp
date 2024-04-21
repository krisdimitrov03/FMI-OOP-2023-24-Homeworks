#pragma once

#include "../../include/utils/FuncResultArr.h"
#include <type_traits>
#include <stdexcept>

utils::func::FuncResultArr::FuncResultArr() : FuncResultArr(INITIAL_CAPACITY)
{
}

utils::func::FuncResultArr::FuncResultArr(size_t capacity)
{
	if (capacity > INITIAL_CAPACITY)
		_cap = capacity;

	_values = new FuncResult[_cap];
}

utils::func::FuncResultArr::FuncResultArr(const FuncResultArr& other)
{
	copyFrom(other);
}

utils::func::FuncResultArr::FuncResultArr(FuncResultArr&& other) noexcept
{
	moveFrom(std::move(other));
}

utils::func::FuncResultArr& utils::func::FuncResultArr::operator=(const FuncResultArr& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return (*this);
}

utils::func::FuncResultArr& utils::func::FuncResultArr::operator=(FuncResultArr&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return (*this);
}

utils::func::FuncResultArr::~FuncResultArr()
{
	free();
}

const utils::func::FuncResult* utils::func::FuncResultArr::getByInput(int16_t input) const
{
	for (size_t i = 0; i < _size; i++)
		if (_values[i].input == input)
			return &_values[i];

	return nullptr;
}

utils::func::FuncResult* utils::func::FuncResultArr::getByInput(int16_t input)
{
	for (size_t i = 0; i < _size; i++)
		if (_values[i].input == input)
			return &_values[i];

	return nullptr;
}

size_t utils::func::FuncResultArr::length() const
{
	return _size;
}

void utils::func::FuncResultArr::push(const FuncResult& el)
{
	if (_size == _cap)
		resize(2 * _cap);

	_values[_size++] = el;
}

void utils::func::FuncResultArr::push(FuncResult&& el)
{
	if (_size == _cap)
		resize(2 * _cap);

	_values[_size++] = std::move(el);
}

void utils::func::FuncResultArr::remove(size_t index)
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	for (size_t i = index + 1; i < _size; i++)
		_values[i - 1] = _values[i];

	_size--;
}

void utils::func::FuncResultArr::readBinary(std::ifstream& is)
{
	free();

	is.read((char*)&_cap, sizeof(size_t));
	is.read((char*)&_size, sizeof(size_t));

	_values = new FuncResult[_cap];
	for (size_t i = 0; i < _size; i++)
		is.read((char*)&_values[i], sizeof(FuncResult));
}

void utils::func::FuncResultArr::saveBinary(std::ofstream& os) const
{
	os.write((const char*)&_cap, sizeof(size_t));
	os.write((const char*)&_size, sizeof(size_t));

	for (size_t i = 0; i < _size; i++)
		os.write((const char*)&_values[i], sizeof(FuncResult));
}

utils::func::FuncResult& utils::func::FuncResultArr::operator[](size_t index)
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	return _values[index];
}

const utils::func::FuncResult& utils::func::FuncResultArr::operator[](size_t index) const
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	return _values[index];
}

void utils::func::FuncResultArr::free()
{
	delete[] _values;
	_values = nullptr;

	_size = 0;
	_cap = INITIAL_CAPACITY;
}

void utils::func::FuncResultArr::copyFrom(const FuncResultArr& other)
{
	_cap = other._cap;
	_size = other._size;

	_values = new FuncResult[_cap];
	for (size_t i = 0; i < _size; i++)
		_values[i] = other._values[i];
}

void utils::func::FuncResultArr::moveFrom(FuncResultArr&& other) noexcept
{
	_cap = other._cap;
	_size = other._size;
	_values = other._values;

	other._values = nullptr;
	other._size = 0;
	other._cap = INITIAL_CAPACITY;
}

void utils::func::FuncResultArr::resize(size_t newCapacity)
{
	if (newCapacity <= _cap)
		throw std::invalid_argument(INVALID_NEW_CAP_ERR_MSG);

	_cap = newCapacity;

	FuncResult* oldValues = _values;

	_values = new FuncResult[_cap];
	for (size_t i = 0; i < _size; i++)
		_values[i] = oldValues[i];

	delete[] oldValues;
}
