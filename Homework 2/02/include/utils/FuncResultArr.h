#pragma once
#include <cstdint>
#include <fstream>
#include "FuncResult.h"

namespace utils {
	namespace func {


		class FuncResultArr {
		private:
			static constexpr size_t INITIAL_CAPACITY = 8;
			static constexpr char INVALID_NEW_CAP_ERR_MSG[] = "Invalid new capacity";
			static constexpr char OUT_OF_RANGE_ERR_MSG[] = "Index out of range";

		public:
			FuncResultArr();
			FuncResultArr(size_t capacity);
			FuncResultArr(const FuncResultArr& other);
			FuncResultArr(FuncResultArr&& other) noexcept;

			FuncResultArr& operator=(const FuncResultArr& other);
			FuncResultArr& operator=(FuncResultArr&& other) noexcept;

			~FuncResultArr();

			const FuncResult* getByInput(int16_t input) const;
			FuncResult* getByInput(int16_t input);

			size_t length() const;

			void push(const FuncResult& el);
			void push(FuncResult&& el);

			void remove(size_t index);

			void readBinary(std::ifstream& is);
			void saveBinary(std::ofstream& os) const;

			FuncResult& operator[](size_t index);
			const FuncResult& operator[](size_t index) const;

		private:
			FuncResult* _values = nullptr;
			size_t _size = 0;
			size_t _cap = INITIAL_CAPACITY;

			void free();
			void copyFrom(const FuncResultArr& other);
			void moveFrom(FuncResultArr&& other) noexcept;
			void resize(size_t newCapacity);
		};

	}
}