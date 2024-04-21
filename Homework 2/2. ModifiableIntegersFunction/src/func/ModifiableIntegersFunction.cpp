#include "../../include/func/ModifiableIntegersFunction.h"
#include "../../include/utils/validation.h"
#include <stdexcept>
#include "../../include/utils/DynamicSet.h"

using namespace utils::guard;

ModifiableIntegersFunction::ModifiableIntegersFunction() : ModifiableIntegersFunction([](int16_t x) -> int16_t { return x; })
{
}

ModifiableIntegersFunction::ModifiableIntegersFunction(Int16Func func)
{
	validateNullptr(func);

	_funcs.push(func);
}

void ModifiableIntegersFunction::changeResult(int16_t input, int16_t newResult)
{
	FuncResult* res = _changed.getByInput(input);

	if (!res) {
		_changed.push({ input, newResult, Status::Changed });
	}
	else {
		res->result = newResult;
		res->status = Status::Changed;
	}
}

void ModifiableIntegersFunction::makeUndefined(int16_t number)
{
	FuncResult* res = _changed.getByInput(number);

	if (!res) {
		_changed.push({ number, -1, Status::Undefined });
	}
	else {
		res->result = -1;
		res->status = Status::Undefined;
	}
}

bool ModifiableIntegersFunction::isInjection() const
{
	utils::DynamicSet set(2 * INT16_MAX + 1);

	for (int x = INT16_MIN; x < INT16_MAX; x++)
	{
		int y = (*this)(x);

		if (set.contains(INT16_MAX + y + 1))
			return false;

		set.add(INT16_MAX + y + 1);
	}

	return true;
}

bool ModifiableIntegersFunction::isSurjection() const
{
	utils::DynamicSet set(2 * INT16_MAX + 1);

	for (int x = INT16_MIN; x < INT16_MAX; x++)
	{
		int y = (*this)(x);
		set.add(INT16_MAX + y + 1);
	}

	return set.length() == 2 * INT16_MAX + 1;
}

bool ModifiableIntegersFunction::isBijection() const
{
	return isInjection() && isSurjection();
}

void ModifiableIntegersFunction::print(int16_t x1, int16_t y1, int16_t x2, int16_t y2) const
{
	char ocs[21][21]{ 0 };

	for (int16_t x = x1; x <= x2; x++)
	{
		int16_t y = (*this)(x);

		if (y >= y1 && y <= y2)
			ocs[x - x1][y2 - y] = '.';
	}

	for (size_t i = 0; i < 21; i++)
	{
		for (size_t j = 0; j < 21; j++)
		{
			if (ocs[i][j] == '.')
				std::cout << ".";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void ModifiableIntegersFunction::load(const char* fileName)
{
	validateNullptr(fileName);

	std::ifstream ifs(fileName, std::ios::binary);

	validateFileStreamOpen(ifs);

	for (int i = INT16_MIN; i < INT16_MAX; i++) {
		FuncResult r;
		r.input = i;

		ifs.read((char*)&r.result, sizeof(int16_t));

		if (r.result == INT16_MIN)
			r.status == Status::Undefined;

		r.status = Status::Changed;

		_changed.push(r);
	}

	ifs.close();
}

void ModifiableIntegersFunction::save(const char* fileName) const
{
	validateNullptr(fileName);

	std::ofstream ofs(fileName, std::ios::binary);

	validateFileStreamOpen(ofs);

	const int16_t min = INT16_MIN;
	for (int i = INT16_MIN; i < INT16_MAX; i++) {
		if (isUndefined(i)) {
			ofs.write((const char*)&min, sizeof(int16_t));
		}
		else {
			int16_t y = (*this)(i);
			ofs.write((const char*)&y, sizeof(int16_t));
		}
	}

	ofs.close();
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const
{
	if (isUndefined(input))
		return INT16_MIN;

	const FuncResult* changedRes = _changed.getByInput(input);

	if (changedRes)
		return changedRes->result;

	return invoke(input);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
	for (int i = INT16_MIN; i <= INT16_MAX; i++)
	{
		if (isUndefined(i) || other.isUndefined(i))
			makeUndefined(i);
		else {
			int thisResult = (*this)(i);
			int otherResult = (other)(i);

			changeResult(i, thisResult + otherResult);
		}
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
	for (int i = INT16_MIN; i <= INT16_MAX; i++)
	{
		if (isUndefined(i) || other.isUndefined(i))
			makeUndefined(i);
		else {
			int thisResult = (*this)(i);
			int otherResult = (other)(i);

			changeResult(i, thisResult - otherResult);
		}
	}

	return *this;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int k) const
{
	ModifiableIntegersFunction result(*this);

	for (int i = 0; i < k - 1; i++)
		result._funcs.push(*this->_funcs[0]);

	result._behaviour = FuncBehaviour::Normal;

	return result;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator~() const
{
	if (!isBijection())
		throw std::runtime_error("function must be bijection to get its inverse");

	ModifiableIntegersFunction result(*this);
	result._behaviour = FuncBehaviour::Reverse;

	return result;
}

bool ModifiableIntegersFunction::isUndefined(int16_t number) const
{
	const FuncResult* res = _changed.getByInput(number);

	if (!res)
		return false;

	return res->status == Status::Undefined;
}

int16_t ModifiableIntegersFunction::invoke(int16_t number) const
{
	int64_t res = number;

	if (_behaviour == FuncBehaviour::Normal) {
		for (size_t i = 0; i < _funcs.length(); i++)
			res = _funcs[i](res);
	}
	else {
		for (size_t i = _funcs.length(); i > 0; i--)
			res = _funcs[i - 1](res);
	}

	if (overflows(res))
		throw std::invalid_argument(OVERFLOW_ERR_MSG);

	return (int16_t)res;
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction result = lhs;
	result += rhs;
	return result;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction result = lhs;
	result -= rhs;
	return result;
}

ModifiableIntegersFunction operator*(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction result(rhs);

	if (lhs._behaviour == FuncBehaviour::Reverse)
		for (int i = lhs._funcs.length(); i > 0; i--)
			result._funcs.push(lhs._funcs[i - 1]);
	else
		for (size_t i = 0; i < lhs._funcs.length(); i++)
			result._funcs.push(lhs._funcs[i]);

	result._behaviour == FuncBehaviour::Normal;

	for (int i = INT16_MIN; i < INT16_MAX; i++) {
		if (lhs.isUndefined(i) || rhs.isUndefined(i))
			result.makeUndefined(i);

		const FuncResult* res = lhs._changed.getByInput(rhs(i));
		if (res)
			result.changeResult(i, res->result);
	}

	return result;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = INT16_MIN; i < INT16_MAX; i++)
		if (lhs(i) >= rhs(i))
			return false;

	return true;
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = INT16_MIN; i < INT16_MAX; i++)
		if (lhs(i) <= rhs(i))
			return false;

	return true;
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int i = INT16_MIN; i <= INT16_MAX; i++)
		if (lhs((int16_t)i) != rhs((int16_t)i))
			return false;

	return true;
}

bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs == rhs);
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
	double ratio = 0.0;

	for (int i = INT16_MIN; i <= INT16_MAX; i += 100) {
		int16_t leftRes = lhs(i);
		int16_t rightRes = rhs(i);

		if (rightRes != 0) {
			double currentRatio = (double)(leftRes) / rightRes;

			if (std::abs(currentRatio - ratio) > 0.00001)
				return false;

			ratio = currentRatio;
		}
	}

	return true;
}
