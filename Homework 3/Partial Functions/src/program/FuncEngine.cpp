#include "../../include/program/FuncEngine.h"
#include "../../include/program/FuncCreator.h"
#include <cstring>

namespace {
	void readInput(char* buff) {
		std::cin.getline(buff, 1024);
		buff[4] = '\0';
	}
}

program::FuncEngine::FuncEngine(const char* filePath)
{
	if (!filePath)
		throw std::invalid_argument("File path is null");

	_function = program::FuncCreator::loadFunc(filePath);
}

program::FuncEngine::FuncEngine(func::PartialFunction*& func) : _function(func)
{
	func = nullptr;
}

void program::FuncEngine::run() const
{
	std::cout << "Choose mode: 1 - range, 2 - sequential result generation" << std::endl;
	int mode;
	std::cin >> mode;

	switch (mode) {
	case 1:
		runRangeMode();
		break;
	case 2:
		runResultGenerationMode();
		break;
	default:
		std::cout << "Invalid mode" << std::endl;
		break;
	}
}

void program::FuncEngine::runRangeMode() const
{
	int32_t left, right;

	std::cout << "Enter range minimum: " << std::endl;
	std::cin >> left;
	std::cout << "Enter range maximum: " << std::endl;
	std::cin >> right;

	for (int32_t i = left; i <= right; i++)
	{
		util::Pair<bool, int32_t> result = _function->invoke(i);

		if (result.getFirst())
			std::cout << "f(" << i << ") = " << result.getSecond() << std::endl;
		else
			std::cout << "f(" << i << ") = undefined" << std::endl;
	}
}

void program::FuncEngine::runResultGenerationMode() const
{
	bool isOver = false;

	int32_t currentValue = getNextDefinedValue(INT32_MIN, isOver);

	char buff[1024];
	readInput(buff);

	while (strcmp(buff, "exit") != 0) {
		if (isOver)
			return;

		int32_t result = _function->invoke(currentValue).getSecond();

		std::cout << "f(" << currentValue << ") = " << result << std::endl;

		readInput(buff);
		currentValue = getNextDefinedValue(currentValue + 1, isOver);
	}
}

int32_t program::FuncEngine::getNextDefinedValue(int32_t current, bool& isOver) const
{
	if (current == INT32_MAX) {
		isOver = true;
		return current;
	}

	for (int64_t value = current; value <= INT32_MAX; ++value)
		if (_function->isDefinedAt(value))
			return value;

	isOver = true;
	return current;
}
