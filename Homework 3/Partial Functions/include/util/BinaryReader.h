#pragma once
#include <fstream>
#include "String.h"

namespace util {

	class BinaryReader
	{
	public:
		BinaryReader(const char* filename);

		BinaryReader(const BinaryReader&) = delete;
		BinaryReader& operator=(const BinaryReader&) = delete;

		BinaryReader(BinaryReader&&) = delete;
		BinaryReader& operator=(BinaryReader&&) = delete;

		uint16_t readUInt16();
		int32_t readInt32();
		String readString();

		void skip(size_t count);

		void close();

		~BinaryReader();

	private:
		std::ifstream _file;
	};

}