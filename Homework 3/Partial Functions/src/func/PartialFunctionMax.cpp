#include "../../include/func/PartialFunctionMax.h"

func::PartialFunctionMax::PartialFunctionMax(const util::PolymorphicContainer<PartialFunction>& funcs) : PartialFunctionComplex(funcs)
{
}

func::PartialFunctionMax::PartialFunctionMax(util::PolymorphicContainer<PartialFunction>&& funcs) : PartialFunctionComplex(std::move(funcs))
{
}

util::Pair<bool, int32_t> func::PartialFunctionMax::invoke(int32_t arg) const
{
	if (!isDefinedAt(arg))
		return util::Pair<bool, int32_t>(false, 0);

	int32_t max = INT32_MIN;

	for (size_t i = 0; i < getFuncs().size(); ++i)
	{
		util::Pair<bool, int32_t> result = (*getFuncs()[i]).invoke(arg);

		if (result.getFirst() && result.getSecond() > max)
			max = result.getSecond();
	}

	return util::Pair<bool, int32_t>(true, max);
}

func::PartialFunction* func::PartialFunctionMax::clone() const
{
	return new PartialFunctionMax(*this);
}