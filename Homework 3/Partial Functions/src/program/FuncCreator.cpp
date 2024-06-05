#include "../../include/program/FuncCreator.h"
#include "../../include/util/PolymorphicContainer.hpp"
#include "../../include/func/PartialFunctionByCriteria.hpp"
#include "../../include/func/PartialFunctionMax.h"
#include "../../include/func/PartialFunctionMin.h"
#include "../../include/program/criteria/IncludeCriteria.h"
#include "../../include/program/criteria/ExcludeCriteria.h"
#include "../../include/program/criteria/OneOrZeroCriteria.h"

func::PartialFunction* program::FuncCreator::loadFunc(const char* filename)
{
	util::BinaryReader reader(filename);

	uint16_t N = reader.readUInt16();
	uint16_t T = reader.readUInt16();

	switch (T) {
	case 0: {
		return createFunc(reader, N, CreateMode::Include);
	}
	case 1: {
		return createFunc(reader, N, CreateMode::Exclude);
	}
	case 2: {
		return createFunc(reader, N, CreateMode::OneOrZero);
	}
	case 3: {
		util::Vector<util::String> names = readFileNames(reader, N);

		util::PolymorphicContainer<func::PartialFunction> container;

		for (size_t i = 0; i < names.getSize(); i++) {
			func::PartialFunction* func = loadFunc(names[i].c_str());
			container.add(func);
		}

		return new func::PartialFunctionMax(container);
	}
	case 4: {
		util::Vector<util::String> names = readFileNames(reader, N);

		util::PolymorphicContainer<func::PartialFunction> container;

		for (size_t i = 0; i < names.getSize(); i++) {
			func::PartialFunction* func = loadFunc(names[i].c_str());
			container.add(func);
		}

		return new func::PartialFunctionMin(container);
	}
	default:
		throw std::runtime_error("Invalid file format");
	}
}

util::Vector<util::String> program::FuncCreator::readFileNames(util::BinaryReader& reader, size_t count)
{
	util::Vector<util::String> names(count);

	for (size_t i = 0; i < count; i++) {
		util::String name = reader.readString();
		reader.skip(1);

		names.pushBack(name);
	}

	return names;
}

func::PartialFunction* program::FuncCreator::createFunc(util::BinaryReader& reader, uint16_t n, CreateMode mode)
{
	switch (mode) {
	case CreateMode::Include: {
		util::Vector<util::Pair<int32_t, int32_t>> values = readPairFuncValues(reader, n);

		return new func::PartialFunctionByCriteria<criteria::IncludeCriteria>(values);
	}
	case CreateMode::Exclude: {
		util::Vector<int32_t> excluded = readFuncValues(reader, n);

		return new func::PartialFunctionByCriteria<criteria::ExcludeCriteria>(excluded);
	}
	case CreateMode::OneOrZero: {
		util::Vector<int32_t> valuesForOne = readFuncValues(reader, n);

		return new func::PartialFunctionByCriteria<criteria::OneOrZeroCriteria>(valuesForOne);
	}
	}
}

util::Vector<util::Pair<int32_t, int32_t>> program::FuncCreator::readPairFuncValues(util::BinaryReader& reader, uint16_t n)
{
	util::Vector<int32_t> domain(n);
	util::Vector<int32_t> range(n);

	for (size_t i = 0; i < n; i++)
		domain.pushBack(reader.readInt32());

	for (size_t i = 0; i < n; i++)
		range.pushBack(reader.readInt32());

	util::Vector<util::Pair<int32_t, int32_t>> values(n);

	for (size_t i = 0; i < n; i++)
		values.pushBack(util::Pair<int32_t, int32_t>(domain[i], range[i]));

	return values;
}

util::Vector<int32_t> program::FuncCreator::readFuncValues(util::BinaryReader& reader, uint16_t n)
{
	util::Vector<int32_t> values(n);

	for (size_t i = 0; i < n; i++)
		values.pushBack(reader.readInt32());

	return values;
}