#pragma once

#include <cstdint>
#include <fstream>

namespace utils {
	namespace func {

		typedef int16_t(*Int16Func)(int16_t);

		class Int16FuncArr {
		private:
			static constexpr size_t INITIAL_CAPACITY = 8;
			static constexpr char INVALID_NEW_CAP_ERR_MSG[] = "Invalid new capacity";
			static constexpr char OUT_OF_RANGE_ERR_MSG[] = "Index out of range";

		public:
			Int16FuncArr();
			Int16FuncArr(size_t capacity);
			Int16FuncArr(const Int16FuncArr& other);
			Int16FuncArr(Int16FuncArr&& other) noexcept;

			Int16FuncArr& operator=(const Int16FuncArr& other);
			Int16FuncArr& operator=(Int16FuncArr&& other) noexcept;

			~Int16FuncArr();

			size_t length() const;

			void push(Int16Func el);

			void remove(size_t index);

			void readBinary(std::ifstream& is);
			void saveBinary(std::ofstream& os) const;

			Int16Func& operator[](size_t index);
			const Int16Func& operator[](size_t index) const;

		private:
			Int16Func* _values = nullptr;
			size_t _size = 0;
			size_t _cap = INITIAL_CAPACITY;

			void free();
			void copyFrom(const Int16FuncArr& other);
			void moveFrom(Int16FuncArr&& other) noexcept;
			void resize(size_t newCapacity);
		};
	
	}
}