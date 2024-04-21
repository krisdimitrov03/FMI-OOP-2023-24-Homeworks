#include "../../include//utils/FuncResult.h"

bool utils::func::operator==(const FuncResult& lhs, const FuncResult& rhs)
{
	return lhs.input == rhs.input && lhs.result == rhs.result && lhs.status == rhs.status;
}

bool utils::func::operator!=(const FuncResult& lhs, const FuncResult& rhs)
{
	return !(lhs == rhs);
}
