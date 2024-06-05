// Taken from https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/blob/1179ebaf94a4ea09c828d78a0f59f2f3bb751fe8/Sem.%2013/Solutions/polymorphic/polymorphic_container.hpp

#pragma once
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

namespace util {

	template<typename TBase>
	class PolymorphicContainer {
	private:
		Vector<PolymorphicPtr<TBase>> ptrs;

	public:
		PolymorphicContainer() = default;
		PolymorphicContainer(size_t capacity);
		PolymorphicContainer(TBase** elements, size_t size);

		void add(TBase* ptr);
		void execute(size_t index, void(*func)(TBase*));
		void execute(size_t index, void(*func)(const TBase*)) const;

		size_t size() const;

		TBase* operator[](size_t index);
		const TBase* operator[](size_t index) const;
	};

}

template<typename TBase>
util::PolymorphicContainer<TBase>::PolymorphicContainer(size_t capacity) : ptrs(capacity) {
}

template<typename TBase>
inline util::PolymorphicContainer<TBase>::PolymorphicContainer(TBase** elements, size_t size) : ptrs(size)
{
	for (size_t i = 0; i < size; i++)
		ptrs[i] = elements[i]->clone();
}

template<typename TBase>
void util::PolymorphicContainer<TBase>::add(TBase* ptr) {
	ptrs.pushBack(ptr);
}

template<typename TBase>
void util::PolymorphicContainer<TBase>::execute(size_t index, void(*func)(TBase*)) {
	func(ptrs[index].get());
}


template<typename TBase>
void util::PolymorphicContainer<TBase>::execute(size_t index, void(*func)(const TBase*)) const {
	func(ptrs[index].get());
}

template<typename TBase>
size_t util::PolymorphicContainer<TBase>::size() const {
	return ptrs.getSize();
}

template<typename TBase>
TBase* util::PolymorphicContainer<TBase>::operator[](size_t index) {
	return ptrs[index].getSize();
}

template<typename TBase>
const TBase* util::PolymorphicContainer<TBase>::operator[](size_t index) const {
	return ptrs[index].get();
}