#include "../../include/utils/validation.h"
#include <stdexcept>

void utils::guard::validateNullptr(utils::func::Int16Func func)
{
	if (!func)
		throw std::invalid_argument(NULLPTR_ERR_MSG);
}

void utils::guard::validateNullptr(const char* str)
{
	if (!str)
		throw std::invalid_argument(NULLPTR_ERR_MSG);
}

void utils::guard::validateFileStreamOpen(const std::ifstream& is)
{
	if (!is.is_open())
		throw std::runtime_error(FILE_NOT_OPEN_ERR_MSG);
}

void utils::guard::validateFileStreamOpen(const std::ofstream& os)
{
	if (!os.is_open())
		throw std::runtime_error(FILE_NOT_OPEN_ERR_MSG);
}

bool utils::guard::overflows(int64_t num)
{
	return num > INT16_MAX || num < INT16_MIN;
}
