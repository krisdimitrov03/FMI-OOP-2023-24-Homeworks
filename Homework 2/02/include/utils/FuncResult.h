#pragma once
#include <cstdint>
#include "Status.h"

namespace utils {
	namespace func {

		struct FuncResult
		{
			int16_t input = 0;
			int16_t result = 0;
			Status status = Status::None;
		};

		bool operator==(const FuncResult& lhs, const FuncResult& rhs);
		bool operator!=(const FuncResult& lhs, const FuncResult& rhs);

	}
}