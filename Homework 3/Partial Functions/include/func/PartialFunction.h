#pragma once

#include <iostream>
#include "../util/Pair.hpp"

namespace func {

	class PartialFunction
	{
	public:
		virtual util::Pair<bool, int32_t> invoke(int32_t arg) const = 0;

		virtual bool isDefinedAt(int32_t arg) const = 0;

		virtual PartialFunction* clone() const = 0;

		virtual ~PartialFunction() = default;
	};

}