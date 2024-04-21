#include <iostream>
#include "include/utils/FuncBehaviour.h"
#include "include/func/ModifiableIntegersFunction.h"

int main()
{
	ModifiableIntegersFunction f;
	ModifiableIntegersFunction g([](int16_t x) -> int16_t { return x * 2; });

	std::cout << f(2) << std::endl;
	std::cout << g(3) << std::endl;

	ModifiableIntegersFunction plus = f + g;
	ModifiableIntegersFunction compose = f * g;
	ModifiableIntegersFunction minus = f - g;

	std::cout << plus(2) << std::endl;
	std::cout << compose(2) << std::endl;
	std::cout << minus(2) << std::endl;
	std::cout << f.isBijection() << std::endl;

	g.save("file.txt");

	ModifiableIntegersFunction h;
	h.load("file.txt");

	std::cout << h(2) << std::endl;
}
