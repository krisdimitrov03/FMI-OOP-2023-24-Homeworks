#pragma once
#include "../func/PartialFunction.h"
#include "../util/Vector.hpp"
#include "../util/String.h"
#include "../util/BinaryReader.h"
#include "CreateMode.h"

namespace program {

	class FuncCreator
	{
	public:
		static func::PartialFunction* loadFunc(const char* filename);

	private:
		static util::Vector<util::String> readFileNames(util::BinaryReader& reader, size_t count);

		static util::Vector<util::Pair<int32_t, int32_t>> readPairFuncValues(util::BinaryReader& reader, uint16_t n);

		static util::Vector<int32_t> readFuncValues(util::BinaryReader& reader, uint16_t n);

		static func::PartialFunction* createFunc(util::BinaryReader& reader, uint16_t n, CreateMode mode);
	};

}