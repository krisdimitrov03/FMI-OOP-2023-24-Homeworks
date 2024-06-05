#include "../../include/func/PartialFunctionComplex.h"

func::PartialFunctionComplex::PartialFunctionComplex(const util::PolymorphicContainer<PartialFunction>& funcs) : _funcs(funcs)
{
}

func::PartialFunctionComplex::PartialFunctionComplex(util::PolymorphicContainer<PartialFunction>&& funcs) : _funcs(std::move(funcs))
{
}

bool func::PartialFunctionComplex::isDefinedAt(int32_t arg) const
{
	for (size_t i = 0; i < _funcs.size(); ++i)
	{
		if (!(*_funcs[i]).isDefinedAt(arg))
			return false;
	}

	return true;
}

util::PolymorphicContainer<func::PartialFunction>& func::PartialFunctionComplex::getFuncs()
{
	return _funcs;
}

const util::PolymorphicContainer<func::PartialFunction>& func::PartialFunctionComplex::getFuncs() const
{
	return _funcs;
}
