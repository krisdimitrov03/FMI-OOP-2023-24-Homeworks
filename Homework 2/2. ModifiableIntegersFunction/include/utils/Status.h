#pragma once
#include <cstdint>

namespace utils {
	namespace func {

		enum class Status : uint8_t
		{
			None = 0,
			Undefined,
			Changed
		};

	}
}