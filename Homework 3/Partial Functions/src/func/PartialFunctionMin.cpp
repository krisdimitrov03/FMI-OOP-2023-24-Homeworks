#include "../../include/func/PartialFunctionMin.h"

func::PartialFunctionMin::PartialFunctionMin(const util::PolymorphicContainer<PartialFunction>& funcs) : PartialFunctionComplex(funcs)
{
}

func::PartialFunctionMin::PartialFunctionMin(util::PolymorphicContainer<PartialFunction>&& funcs) : PartialFunctionComplex(std::move(funcs))
{
}

util::Pair<bool, int32_t> func::PartialFunctionMin::invoke(int32_t arg) const
{
	if (!isDefinedAt(arg))
		return util::Pair<bool, int32_t>(false, 0);

	int32_t min = INT32_MAX;

	for (size_t i = 0; i < getFuncs().size(); ++i)
	{
		util::Pair<bool, int32_t> result = (*getFuncs()[i]).invoke(arg);

		if (result.getFirst() && result.getSecond() < min)
			min = result.getSecond();
	}

	return util::Pair<bool, int32_t>(true, min);
}

func::PartialFunction* func::PartialFunctionMin::clone() const
{
	return new PartialFunctionMin(*this);
}