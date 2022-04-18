#include <iostream>
#include <numeric>

#include "matrix_generator.h"
#include "profile.h"
#include "doctest.h"

void MultiplicationBenchmark() {
	Matrix::MatrixGenerator gen;
	for (size_t i = 16; i <= 2048; i *= 2) {
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
			LOG_DURATION("Single-threaded Strassen");
			sth_strassen = Matrix::StrassenAlgorithm(lhs, rhs, 64);
		}

		{
			LOG_DURATION("Multi-threaded Strassen");
			mth_strassen = Matrix::StrassenAlgorithm(lhs, rhs, 64, true);
		}

		if (naive != sth_strassen || naive != mth_strassen) {
			throw std::runtime_error("Unexpected result");
		}
	}
}

int main() {
	char command;
	do {
		std::cout << "[1] Run tests\n"
				  << "[2] Benchmark\n"
				  << "[3] Exit\n\n";
		std::cin >> command;
		switch (command) {
			case '1': {
				doctest::Context context;
				context.run();
				break;
			}
			case '2': 
				MultiplicationBenchmark();
		}
	} while (command != '3');
}

