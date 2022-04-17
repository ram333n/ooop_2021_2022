#include <iostream>
#include <numeric>

#include "matrix_generator.h"
#include "profile.h"
#include "doctest.h"

void Benchmark() {
	std::cout << "Enter max dimension of matrix\n";
	size_t max_dimension = 0;
	std::cin >> max_dimension;
	Matrix::MatrixGenerator gen;

	for (size_t i = 16; i <= max_dimension; i *= 2) {
		Matrix::Matrix<int> naive, sth_strassen, mth_strassen;

		Matrix::Matrix<int> lhs = gen(i, i);
		Matrix::Matrix<int> rhs = gen(i, i);

		std::cout << "-----------------------------------\n";
		std::cout << "Dimension : " << i << '\n';
		{
			LOG_DURATION("Naive algorithm");
			naive = Matrix::NaiveMultiplication(lhs, rhs);
		}

		{
			LOG_DURATION("Single threaded Strassen");
			sth_strassen = Matrix::StrassenAlgorithm(lhs, rhs, 64);
		}

		{
			LOG_DURATION("Multi threaded Strassen");
			mth_strassen = Matrix::StrassenAlgorithm(lhs, rhs, 64, true);
		}

		bool is_correct = (naive == sth_strassen) && (naive == mth_strassen);
		if (!is_correct) {
			throw std::runtime_error("Unexpected result");
		}
	}
}


int main() {
	doctest::Context runner;
	runner.run();

	Benchmark();
}
