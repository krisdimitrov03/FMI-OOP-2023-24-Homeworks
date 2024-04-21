#pragma once

#include "Int16FuncArr.h";

namespace utils {
	namespace guard {

		const char NULLPTR_ERR_MSG[] = "Nullptr argument";
		const char FUNC_UNDEF_ERR_MSG[] = "Function undefined for this input";
		const char OVERFLOW_ERR_MSG[] = "Function result for this input overflows 16-bit numbers";
		const char FILE_NOT_OPEN_ERR_MSG[] = "File could not be open";

		void validateNullptr(func::Int16Func func);

		void validateNullptr(const char* str);

		void validateFileStreamOpen(const std::ifstream& is);

		void validateFileStreamOpen(const std::ofstream& os);

		bool overflows(int64_t num);
	}
}