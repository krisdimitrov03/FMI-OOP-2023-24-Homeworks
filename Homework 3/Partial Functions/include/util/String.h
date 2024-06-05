// Taken from https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2009/MyString%20(with%20move)/MyString.h

#pragma once
#include <iostream>

namespace util {

	class String
	{
	public:
		String();
		String(const char* data);

		String(const String& other);
		String& operator=(const String& other);
		~String();

		size_t getCapacity() const;
		size_t getSize() const;

		const char* c_str() const;

		String& operator+=(const String& other);

		char& operator[](size_t index);
		const char& operator[](size_t index) const;

		friend std::ostream& operator<<(std::ostream& os, const String& obj);
		friend std::istream& operator>>(std::istream& is, String& ref);
		friend String operator+(const String& lhs, const String& rhs);
	private:
		explicit String(size_t stringLength);
		void resize(unsigned newAllocatedDataSize);

		void free();
		void copyFrom(const String& other);

		char* _data;
		size_t _size;
		size_t _allocatedDataSize;
	};

	bool operator==(const util::String& lhs, const util::String& rhs);
	bool operator!=(const util::String& lhs, const util::String& rhs);
	bool operator<(const util::String& lhs, const util::String& rhs);
	bool operator<=(const util::String& lhs, const util::String& rhs);
	bool operator>(const util::String& lhs, const util::String& rhs);
	bool operator>=(const util::String& lhs, const util::String& rhs);

}