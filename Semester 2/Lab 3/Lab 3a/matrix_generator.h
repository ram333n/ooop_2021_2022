#pragma once

#include <random>
#include "matrix.h"

namespace Matrix {
	class MatrixGenerator {
	public:
		MatrixGenerator() : dist{ 0, 100 } {}
		MatrixGenerator(int range_begin, int range_end) : dist{ range_begin, range_end } {}

		[[nodiscard]] Matrix<int> operator()(size_t rows, size_t columns) {
			Matrix<int> result(rows, columns);

			for (size_t i = 0; i < rows; ++i) {
				for (size_t j = 0; j < columns; ++j) {
					result.At(i, j) = dist(gen);
				}
			}

			return result;
		}

	private:
		std::mt19937 gen;
		std::uniform_int_distribution<int> dist;
	};
}