#include "../../include/util/BinaryReader.h"

util::BinaryReader::BinaryReader(const char* filename)
{
	if (!filename)
		throw std::invalid_argument("filename is null");

	_file.open(filename, std::ios::binary);

	if (!_file.is_open())
		throw std::runtime_error("Failed to open file");
}

uint16_t util::BinaryReader::readUInt16()
{
	uint16_t value = 0;

	_file.read((char*)&value, sizeof(uint16_t));

	return value;
}

int32_t util::BinaryReader::readInt32()
{
	int32_t value = 0;

	_file.read((char*)&value, sizeof(int32_t));

	return value;
}

util::String util::BinaryReader::readString()
{
	char buffer[1024];

	_file.get(buffer, sizeof(buffer), '\0');

	return String(buffer);
}

void util::BinaryReader::skip(size_t count)
{
	for (size_t i = 0; i < count; i++)
		_file.get();
}

void util::BinaryReader::close()
{
	if (_file.is_open())
		_file.close();
}

util::BinaryReader::~BinaryReader()
{
	close();
}
