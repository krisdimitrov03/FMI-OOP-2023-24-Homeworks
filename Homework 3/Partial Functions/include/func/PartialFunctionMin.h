#pragma once

#include "PartialFunctionComplex.h"
#include "../../include/util/PolymorphicContainer.hpp"

namespace func {

	class PartialFunctionMin : public PartialFunctionComplex
	{
	public:
		PartialFunctionMin(const util::PolymorphicContainer<PartialFunction>& funcs);
		PartialFunctionMin(util::PolymorphicContainer<PartialFunction>&& funcs);

		util::Pair<bool, int32_t> invoke(int32_t arg) const override;

		PartialFunction* clone() const override;
	};

}