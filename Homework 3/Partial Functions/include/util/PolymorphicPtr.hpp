// Taken from https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/blob/1179ebaf94a4ea09c828d78a0f59f2f3bb751fe8/Sem.%2013/Solutions/polymorphic/polymorphic_ptr.hpp

#pragma once
#include <utility>

namespace util {

	template<typename T>
	class PolymorphicPtr {
	private:
		T* ptr = nullptr;
	public:
		PolymorphicPtr() = default;
		PolymorphicPtr(T* ptr);
		PolymorphicPtr(const PolymorphicPtr<T>& other);
		PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
		PolymorphicPtr<T>& operator=(const PolymorphicPtr<T>& other);
		PolymorphicPtr<T>& operator=(PolymorphicPtr<T>&& other) noexcept;
		~PolymorphicPtr();

		T* operator->();
		const T* operator->() const;
		T& operator*();
		const T& operator*() const;

		T* get();
		const T* get() const;
		void reset(T* ptr);
		T* release(); // releases the ownership of the pointer

	private:
		void free();
		void copyFrom(const PolymorphicPtr& other);
		void moveFrom(PolymorphicPtr&& other);
	};

}


template<typename T>
util::PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : ptr(ptr)
{ }

template<typename T>
util::PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other) {
	copyFrom(other);
}

template<typename T>
util::PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template<typename T>
util::PolymorphicPtr<T>& util::PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
util::PolymorphicPtr<T>& util::PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
util::PolymorphicPtr<T>::~PolymorphicPtr() {
	free();
}

template<typename T>
T* util::PolymorphicPtr<T>::operator->() {
	return ptr;
}

template<typename T>
const T* util::PolymorphicPtr<T>::operator->() const {
	return ptr;
}

template<typename T>
T& util::PolymorphicPtr<T>::operator*() {
	return *ptr;
}

template<typename T>
const T& util::PolymorphicPtr<T>::operator*() const {
	return *ptr;
}

template<typename T>
T* util::PolymorphicPtr<T>::get() {
	return ptr;
}

template<typename T>
const T* util::PolymorphicPtr<T>::get() const {
	return ptr;
}

template<typename T>
void util::PolymorphicPtr<T>::reset(T* ptr) {
	free();
	this->ptr = ptr;
}

template<typename T>
T* util::PolymorphicPtr<T>::release() {
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

template<typename T>
void util::PolymorphicPtr<T>::free() {
	delete ptr;
}

template<typename T>
void util::PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other) {
	ptr = other.ptr->clone();
}

template<typename T>
void util::PolymorphicPtr<T>::moveFrom(PolymorphicPtr&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}