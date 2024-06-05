#pragma once

#include "../../util/Vector.hpp"
#include "../../util/Pair.hpp"

namespace program {
	namespace criteria {

		class IncludeCriteria {
		public:
			IncludeCriteria(const util::Vector<util::Pair<int32_t, int32_t>>& values);

			util::Pair<bool, int32_t> operator()(int32_t x) const;

		private:
			util::Vector<util::Pair<int32_t, int32_t>> _values;
		};

	}
}