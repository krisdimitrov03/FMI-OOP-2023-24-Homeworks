#include "../../../include/program/criteria/OneOrZeroCriteria.h"

program::criteria::OneOrZeroCriteria::OneOrZeroCriteria(const util::Vector<int32_t>& values) : _values(values)
{
}

util::Pair<bool, int32_t> program::criteria::OneOrZeroCriteria::operator()(int32_t x) const
{
	for (size_t i = 0; i < _values.getSize(); i++)
		if (_values[i] == x)
			return util::Pair<bool, int32_t>(true, 1);

	return util::Pair<bool, int32_t>(true, 0);
}
