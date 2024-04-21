#pragma once

#include "../utils/Int16FuncArr.h"
#include "../utils/FuncResultArr.h"
#include "../utils/FuncBehaviour.h"

using namespace utils::func;

class ModifiableIntegersFunction
{
public:
	ModifiableIntegersFunction();
	ModifiableIntegersFunction(Int16Func func);

	void changeResult(int16_t input, int16_t newResult);
	void makeUndefined(int16_t number);

	bool isInjection() const;

	bool isSurjection() const;

	bool isBijection() const;

	void print(int16_t x1, int16_t y1, int16_t x2, int16_t y2) const;

	void load(const char* fileName);
	void save(const char* fileName) const;

	int16_t operator()(int16_t input) const;

	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);

	ModifiableIntegersFunction operator^(int k) const;
	ModifiableIntegersFunction operator~() const;

	friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend ModifiableIntegersFunction operator*(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

private:
	Int16FuncArr _funcs;
	FuncResultArr _changed;
	FuncBehaviour _behaviour = FuncBehaviour::Normal;

	bool isUndefined(int16_t number) const;
	int16_t invoke(int16_t number) const;
};

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator*(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);