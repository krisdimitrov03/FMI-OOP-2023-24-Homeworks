#pragma once

#include "PartialFunction.h"

namespace func {

	template<typename TFunc>
	class PartialFunctionByCriteria : public PartialFunction
	{
	public:
		PartialFunctionByCriteria(TFunc func);

		util::Pair<bool, int32_t> invoke(int32_t arg) const override;

		bool isDefinedAt(int32_t arg) const override;

		PartialFunction* clone() const override;

	private:
		TFunc _func;
	};

}

template<typename TFunc>
func::PartialFunctionByCriteria<TFunc>::PartialFunctionByCriteria(TFunc func)
	: _func(func)
{
}

template<typename TFunc>
util::Pair<bool, int32_t> func::PartialFunctionByCriteria<TFunc>::invoke(int32_t arg) const
{
	return _func(arg);
}

template<typename TFunc>
bool func::PartialFunctionByCriteria<TFunc>::isDefinedAt(int32_t arg) const
{
	return _func(arg).getFirst();
}

template<typename TFunc>
func::PartialFunction* func::PartialFunctionByCriteria<TFunc>::clone() const
{
	return new PartialFunctionByCriteria<TFunc>(*this);
}
