#pragma once

#include "../../include/utils/Int16FuncArr.h"
#include <type_traits>
#include <stdexcept>

utils::func::Int16FuncArr::Int16FuncArr() : Int16FuncArr(INITIAL_CAPACITY)
{
}

utils::func::Int16FuncArr::Int16FuncArr(size_t capacity)
{
	if (capacity > INITIAL_CAPACITY)
		_cap = capacity;

	_values = new Int16Func[_cap];
}

utils::func::Int16FuncArr::Int16FuncArr(const Int16FuncArr& other)
{
	copyFrom(other);
}

utils::func::Int16FuncArr::Int16FuncArr(Int16FuncArr&& other) noexcept
{
	moveFrom(std::move(other));
}

utils::func::Int16FuncArr& utils::func::Int16FuncArr::operator=(const Int16FuncArr& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return (*this);
}

utils::func::Int16FuncArr& utils::func::Int16FuncArr::operator=(Int16FuncArr&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return (*this);
}

utils::func::Int16FuncArr::~Int16FuncArr()
{
	free();
}

size_t utils::func::Int16FuncArr::length() const
{
	return _size;
}

void utils::func::Int16FuncArr::push(Int16Func el)
{
	if (_size == _cap)
		resize(2 * _cap);

	_values[_size++] = el;
}

void utils::func::Int16FuncArr::remove(size_t index)
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	for (size_t i = index + 1; i < _size; i++)
		_values[i - 1] = _values[i];

	_size--;
}

void utils::func::Int16FuncArr::readBinary(std::ifstream& is)
{
	free();

	is.read((char*)&_cap, sizeof(size_t));
	is.read((char*)&_size, sizeof(size_t));

	_values = new Int16Func[_cap];
	for (size_t i = 0; i < _size; i++)
		is.read((char*)&_values[i], sizeof(Int16Func));
}

void utils::func::Int16FuncArr::saveBinary(std::ofstream& os) const
{
	os.write((const char*)&_cap, sizeof(size_t));
	os.write((const char*)&_size, sizeof(size_t));

	for (size_t i = 0; i < _size; i++)
		os.write((const char*)&_values[i], sizeof(Int16Func));
}

utils::func::Int16Func& utils::func::Int16FuncArr::operator[](size_t index)
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	return _values[index];
}

const utils::func::Int16Func& utils::func::Int16FuncArr::operator[](size_t index) const
{
	if (index >= _size)
		throw std::out_of_range(OUT_OF_RANGE_ERR_MSG);

	return _values[index];
}

void utils::func::Int16FuncArr::free()
{
	delete[] _values;
	_values = nullptr;

	_size = 0;
	_cap = INITIAL_CAPACITY;
}

void utils::func::Int16FuncArr::copyFrom(const Int16FuncArr& other)
{
	_cap = other._cap;
	_size = other._size;

	_values = new Int16Func[_cap];
	for (size_t i = 0; i < _size; i++)
		_values[i] = other._values[i];
}

void utils::func::Int16FuncArr::moveFrom(Int16FuncArr&& other) noexcept
{
	_cap = other._cap;
	_size = other._size;
	_values = other._values;

	other._values = nullptr;
	other._size = 0;
	other._cap = INITIAL_CAPACITY;
}

void utils::func::Int16FuncArr::resize(size_t newCapacity)
{
	if (newCapacity <= _cap)
		throw std::invalid_argument(INVALID_NEW_CAP_ERR_MSG);

	_cap = newCapacity;

	Int16Func* oldValues = _values;

	_values = new Int16Func[_cap];
	for (size_t i = 0; i < _size; i++)
		_values[i] = oldValues[i];

	delete[] oldValues;
}