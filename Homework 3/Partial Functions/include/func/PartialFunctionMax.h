#pragma once

#include "PartialFunctionComplex.h"
#include "../util/PolymorphicContainer.hpp"

namespace func {

	class PartialFunctionMax : public PartialFunctionComplex
	{
	public:
		PartialFunctionMax(const util::PolymorphicContainer<PartialFunction>& funcs);
		PartialFunctionMax(util::PolymorphicContainer<PartialFunction>&& funcs);

		util::Pair<bool, int32_t> invoke(int32_t arg) const override;

		PartialFunction* clone() const override;
	};

}