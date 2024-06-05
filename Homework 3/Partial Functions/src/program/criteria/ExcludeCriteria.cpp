#include "../../../include/program/criteria/ExcludeCriteria.h"

program::criteria::ExcludeCriteria::ExcludeCriteria(const util::Vector<int32_t>& values) : _values(values)
{
}

util::Pair<bool, int32_t> program::criteria::ExcludeCriteria::operator()(int32_t x) const
{
	for (size_t i = 0; i < _values.getSize(); i++)
		if (_values[i] == x)
			return util::Pair<bool, int32_t>(false, 0);

	return util::Pair<bool, int32_t>(true, x);
}
