#pragma once

#include "PartialFunction.h"
#include "../util/PolymorphicContainer.hpp"

namespace func {

	class PartialFunctionComplex : public PartialFunction
	{
	public:
		PartialFunctionComplex(const util::PolymorphicContainer<PartialFunction>& funcs);
		PartialFunctionComplex(util::PolymorphicContainer<PartialFunction>&& funcs);

		bool isDefinedAt(int32_t arg) const override;

	protected:
		util::PolymorphicContainer<PartialFunction>& getFuncs();

		const util::PolymorphicContainer<PartialFunction>& getFuncs() const;

	private:
		util::PolymorphicContainer<PartialFunction> _funcs;
	};

}