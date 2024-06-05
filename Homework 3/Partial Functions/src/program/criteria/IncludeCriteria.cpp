#include "../../../include/program/criteria/IncludeCriteria.h"

program::criteria::IncludeCriteria::IncludeCriteria(const util::Vector<util::Pair<int32_t, int32_t>>& values) :_values(values)
{
}

util::Pair<bool, int32_t> program::criteria::IncludeCriteria::operator()(int32_t x) const
{
	for (size_t i = 0; i < _values.getSize(); i++)
		if (_values[i].getFirst() == x)
			return util::Pair<bool, int32_t>(true, _values[i].getSecond());

	return util::Pair<bool, int32_t>(false, 0);
}
