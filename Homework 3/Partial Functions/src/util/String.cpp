#include "../../include/util/String.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)


static unsigned roundToPowerOfTwo(unsigned v) //static! -> will be discused in the next lecture
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

util::String::String() : String("") {}

util::String::String(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

util::String::String(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

util::String::String(const String& other)
{
    copyFrom(other);
}

util::String& util::String::operator=(const String& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

util::String::~String()
{
    free();
}

size_t util::String::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t util::String::getSize() const
{
    return _size;
}

const char* util::String::c_str() const
{
    return _data;
}

util::String& util::String::operator+=(const String& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    // we need to use strncat instead of strcat, because strcat will not work for str += str 
    // (the terminating zero of str will be destroyed by the first char)
    std::strncat(_data, other._data, other.getSize());

    _size = getSize() + other.getSize();
    return *this;
}

char& util::String::operator[](size_t index)
{
    return _data[index]; // no security check!!
}

const char& util::String::operator[](size_t index) const
{
    return _data[index]; // no security check!!
}

std::ostream& util::operator<<(std::ostream& os, const util::String& obj)
{
    return os << obj._data;
}

std::istream& util::operator>>(std::istream& is, util::String& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void util::String::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void util::String::free()
{
    delete[] _data;
}

void util::String::copyFrom(const String& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

util::String util::operator+(const String& lhs, const String& rhs)
{
    String result(lhs.getSize() + rhs.getSize());
    result += lhs; // no resize is needed
    result += rhs;
    return result;
}

bool util::operator==(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool util::operator!=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool util::operator<(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool util::operator<=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool util::operator>(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool util::operator>=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}