#include "include/program/FuncEngine.h"
#include "include/func/PartialFunctionByCriteria.hpp"

constexpr char FUNC_FILE_PATH[] = "func.dat";

typedef util::Pair<bool, int32_t>(*Func)(int32_t);

util::Pair<bool, int32_t> function(int32_t x) {
	if (x % 2 == 0)
		return util::Pair<bool, int32_t>(true, x);

	else return util::Pair<bool, int32_t>(false, 0);
}

int main()
{
	// Test the program with mock function:
	// 
	// func::PartialFunction* func = new func::PartialFunctionByCriteria<Func>(function);
	// program::FuncEngine engine(func);

	program::FuncEngine engine(FUNC_FILE_PATH);
	engine.run();
}

