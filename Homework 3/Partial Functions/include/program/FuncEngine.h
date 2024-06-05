#pragma once
#include "../func/PartialFunction.h"
#include "../util/PolymorphicPtr.hpp"

namespace program {

	class FuncEngine
	{
	public:
		FuncEngine(const char* filePath);
		FuncEngine(func::PartialFunction*& func);

		void run() const;

	private:
		util::PolymorphicPtr<func::PartialFunction> _function;

		void runRangeMode() const;

		void runResultGenerationMode() const;

		int32_t getNextDefinedValue(int32_t current, bool& isOver) const;
	};
}