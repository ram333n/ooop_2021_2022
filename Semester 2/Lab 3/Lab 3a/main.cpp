#include <iostream>
#include <future>
#include <numeric>

#include "matrix.h"
#include "profile.h"
#include "doctest.h"

TEST_CASE("Matrix") {
	SUBCASE("Default contruct") {
		Matrix::Matrix<int> m;
		CHECK(m.Empty());
		CHECK(m.Columns() == 0);
		CHECK(m.Rows() == 0);
	}

	SUBCASE("Matrix::At") {
		Matrix::Matrix<long> m(3, 3);
		m.At(0, 0) = 1;
		m.At(1, 1) = 4;
		m.At(2, 2) = 9;

		CHECK(m.Columns() == 3);
		CHECK(m.Rows() == 3);
		CHECK(!m.Empty());
		CHECK(m.At(2, 2) == 9);		
	}

	SUBCASE("Copy and move ctors, assignment and equality operators") {
		Matrix::Matrix<int> m_1({ {1,2,3},{6,5,4},{7,8,9} });
		Matrix::Matrix<int> m_2(m_1);

		CHECK(m_1 == m_2);
		CHECK(m_2.At(0, 0) == 1);
		CHECK(m_2.Columns() == 3);
		CHECK(m_2.Rows() == 3);


		Matrix::Matrix<int> m_3 = std::move(m_1);

		CHECK(m_2 == m_3);
		CHECK(m_1.Empty());
		CHECK(m_1.Columns() == 0);
		CHECK(m_1.Rows() == 0);

		m_1 = m_2;
		CHECK(m_1 == m_2);

		Matrix::Matrix<int> m_4;
		m_4 = std::move(m_1);

		CHECK(m_4 == m_3);
		CHECK(m_1.Empty());
		CHECK(m_1.Columns() == 0);
		CHECK(m_1.Rows() == 0);

		m_4.At(0, 1) = 4343;
		CHECK(m_4 != m_3);
		CHECK(m_4 != m_3);

		Matrix::Matrix<int> m_5(3,4);
		CHECK(m_5 != m_3);
	}

	SUBCASE("operators + and -") {
		Matrix::Matrix<int> m_1(
			{
				{ 1,2,3,4 },
				{ 5,6,7,8 },
				{ 9,10,11,12 }
			}
		);

		Matrix::Matrix<int> m_2(
			{
				{ 12,11,10,9 },
				{ 8,7,6,5 },
				{ 4,3,2,1 }
			}
		);

		auto m_3 = m_1;

		auto addition_res = m_1 + m_2;
		auto minus_res = m_1 - m_3;
		for (size_t i = 0; i < addition_res.Rows(); ++i) {
			for (size_t j = 0; j < addition_res.Columns(); ++j) {
				CHECK(addition_res.At(i, j) == 13);
				CHECK(minus_res.At(i, j) == 0);
			}
		}
	}

}


int main() {
	doctest::Context runner;
	runner.run();
}