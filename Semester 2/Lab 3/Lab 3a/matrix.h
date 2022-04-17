#pragma once

#include <iostream>
#include <vector>
#include <type_traits>
#include <future>

namespace Matrix {
	template<typename T>
	class Matrix {
		static_assert(std::is_arithmetic_v<T>, "Unsupported type provided for Matrix");
	public:
		Matrix() = default;
		Matrix(size_t rows_, size_t columns_);
		Matrix(const Matrix& m);
		Matrix(Matrix&& m) noexcept;
		Matrix(const std::vector<std::vector<T>>& data_);
		Matrix(std::vector<std::vector<T>>&& data_) noexcept;

		T& At(size_t row, size_t column);
		const T& At(size_t row, size_t column) const;

		size_t Rows() const;
		size_t Columns() const;

		void Resize(size_t rows, size_t columns);

		bool Empty() const;

		Matrix<T>& operator=(const Matrix<T>& rhs);
		Matrix<T>& operator=(Matrix<T>&& rhs) noexcept;

		template<typename U>
		friend bool operator==(const Matrix<U>& lhs, const Matrix<U>& rhs);

		template<typename U>
		friend bool operator!=(const Matrix<U>& lhs, const Matrix<U>& rhs);

		template<typename U>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);

		template<typename U>
		[[nodiscard]] friend Matrix<U> operator+(const Matrix<U>& lhs, const Matrix<U>& rhs);

		template<typename U>
		[[nodiscard]] friend Matrix<U> operator-(const Matrix<U>& lhs, const Matrix<U>& rhs);

	private:
		std::vector<std::vector<T>> data;
		size_t rows_count = 0, columns_count = 0;
	};

	template<typename T>
	Matrix<T>::Matrix(size_t rows_, size_t columns_) {
		if (rows_ > 0 && columns_ > 0) {
			rows_count = rows_;
			columns_count = columns_;
		}

		data.resize(rows_count);
		for (auto& row : data) {
			row.resize(columns_count, 0);
		}
	}

	template<typename T>
	Matrix<T>::Matrix(const Matrix<T>& m) :
		rows_count(m.rows_count),
		columns_count(m.columns_count),
		data(m.data) {}


	template<typename T>
	Matrix<T>::Matrix(Matrix&& m) noexcept :
		rows_count(std::move(m.rows_count)),
		columns_count(std::move(m.columns_count)),
		data(std::move(m.data)) 
	{
		m.rows_count = m.columns_count = 0;
	}

	template<typename T>
	Matrix<T>::Matrix(const std::vector<std::vector<T>>& data_) {
		if (data_.empty() || data_[0].empty()) {
			Matrix();
		}
		else {
			rows_count = data_.size();
			columns_count = data_[0].size();
			data = data_;
		}
	}

	template<typename T>
	Matrix<T>::Matrix(std::vector<std::vector<T>>&& data_) noexcept {
		if (data_.empty() || data_[0].empty()) {
			rows_count = columns_count = 0;
		}
		else {
			rows_count = data_.size();
			columns_count = data_[0].size();
			data = std::move(data_);
		}
	}

	template<typename T>
	T& Matrix<T>::At(size_t row, size_t column) {
		return data[row][column];
	}

	template<typename T>
	const T& Matrix<T>::At(size_t row, size_t column) const {
		return data[row][column];
	}

	template<typename T>
	size_t Matrix<T>::Rows() const {
		return rows_count;
	}

	template<typename T>
	size_t Matrix<T>::Columns() const {
		return columns_count;
	}

	template<typename T>
	void Matrix<T>::Resize(size_t rows, size_t columns) {
		if (rows == 0 || columns == 0||(rows == rows_count && columns == columns_count)) {
			return;
		}

		data.resize(rows);

		for (auto& row : data) {
			row.resize(columns);
		}

		rows_count = rows;
		columns_count = columns;
	}

	template<typename T>
	bool Matrix<T>::Empty() const {
		return data.empty();
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
		rows_count = rhs.rows_count;
		columns_count = rhs.columns_count;
		data = rhs.data;

		return *this;
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept {
		rows_count = std::move(rhs.rows_count);
		columns_count = std::move(rhs.columns_count);
		data = std::move(rhs.data);
		rhs.rows_count = rhs.columns_count = 0;

		return *this;
	}

	template<typename T>
	bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		return lhs.data == rhs.data;
	}

	template<typename T>
	bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		return lhs.data != rhs.data;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
		for (const auto& row : m.data) {
			for (const T& elem : row) {
				os << elem << '\t';
			}
			os << '\n';
		}

		return os;
	}
	template<typename T>
	[[nodiscard]] Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		if (lhs.rows_count != rhs.rows_count || lhs.columns_count != rhs.columns_count) {
			throw std::invalid_argument("These matrices have different dimensions");
		}

		Matrix<T> result(lhs.rows_count, lhs.columns_count);

		for (size_t i = 0; i < lhs.rows_count; ++i) {
			for (size_t j = 0; j < lhs.columns_count; ++j) {
				result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
			}
		}

		return result;

	}

	template<typename T>
	[[nodiscard]] Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		if (lhs.rows_count != rhs.rows_count || lhs.columns_count != rhs.columns_count) {
			throw std::invalid_argument("These matrices have different dimensions");
		}

		Matrix<T> result(lhs.rows_count, lhs.columns_count);

		for (size_t i = 0; i < lhs.rows_count; ++i) {
			for (size_t j = 0; j < lhs.columns_count; ++j) {
				result.At(i, j) = lhs.At(i, j) - rhs.At(i, j);
			}
		}

		return result;
	}

	template<typename T>
	[[nodiscard]] Matrix<T> NaiveMultiplication(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		if (lhs.Columns() != rhs.Rows() || lhs.Empty() || rhs.Empty()) {
			throw std::invalid_argument("Matrices have wrong dimensions");
		}

		Matrix<T> result(lhs.Rows(), rhs.Columns());

		for (size_t i = 0; i < lhs.Rows(); ++i) {
			for (size_t j = 0; j < rhs.Columns(); ++j) {
				result.At(i,j) = 0;
				for (size_t k = 0; k < rhs.Rows(); ++k) {
					result.At(i, j) += lhs.At(i, k) * rhs.At(k, j);
				}
			}
		}

		return result;
	}

	template<typename T>
	void Split(const Matrix<T>& source, Matrix<T>& A_11, Matrix<T>& A_12, Matrix<T>& A_21, Matrix<T>& A_22) {
		size_t half_size = source.Rows() / 2;

		for (size_t i = 0; i < half_size; ++i) {
			for (size_t j = 0; j < half_size; ++j) {
				A_11.At(i, j) = source.At(i, j);
				A_12.At(i, j) = source.At(i, j + half_size);
				A_21.At(i, j) = source.At(i + half_size, j);
				A_22.At(i, j) = source.At(i + half_size, j + half_size);
			}
		}
	}

	template<typename T>
	void Merge(Matrix<T>& dest, const Matrix<T>& A_11, const Matrix<T>& A_12, const Matrix<T>& A_21, const Matrix<T>& A_22) {
		size_t half_size = A_11.Rows();

		for (size_t i = 0; i < half_size; ++i) {
			for (size_t j = 0; j < half_size; ++j) {
				dest.At(i, j) = A_11.At(i, j);
				dest.At(i, j + half_size) = A_12.At(i, j);
				dest.At(i + half_size, j) = A_21.At(i, j);
				dest.At(i + half_size, j + half_size) = A_22.At(i, j);
			}
		}
	}

	template<typename T>
	Matrix<T> StrassenSingleThread(const Matrix<T>& lhs, const Matrix<T>& rhs, size_t lower_border = 8) {
		if (lhs.Rows() < lower_border) {
			return NaiveMultiplication(lhs, rhs);
		}

		size_t half_size = lhs.Rows() / 2;

		Matrix<T> A_11(half_size, half_size),
				  A_12(half_size, half_size),
				  A_21(half_size, half_size),
				  A_22(half_size, half_size),
				  B_11(half_size, half_size),
				  B_12(half_size, half_size),
				  B_21(half_size, half_size),
				  B_22(half_size, half_size);

		Split(lhs, A_11, A_12, A_21, A_22);
		Split(rhs, B_11, B_12, B_21, B_22);

		Matrix<T> M_1 = StrassenSingleThread(A_11 + A_22, B_11 + B_22, lower_border);
		Matrix<T> M_2 = StrassenSingleThread(A_21 + A_22, B_11, lower_border);
		Matrix<T> M_3 = StrassenSingleThread(A_11, B_12 - B_22, lower_border);
		Matrix<T> M_4 = StrassenSingleThread(A_22, B_21 - B_11, lower_border);
		Matrix<T> M_5 = StrassenSingleThread(A_11 + A_12, B_22, lower_border);
		Matrix<T> M_6 = StrassenSingleThread(A_21 - A_11, B_11 + B_12, lower_border);
		Matrix<T> M_7 = StrassenSingleThread(A_12 - A_22, B_21 + B_22, lower_border);

		Matrix<T> result(lhs.Rows(), rhs.Columns());
		Merge(result, M_1 + M_4 - M_5 + M_7,
					  M_3 + M_5,
					  M_2 + M_4,
					  M_1 - M_2 + M_3 + M_6);

		return result;
	}

	template<typename T>
	Matrix<T> StrassenMultiThread(const Matrix<T>& lhs, const Matrix<T>& rhs, size_t lower_border = 8) {
		if (lhs.Rows() < lower_border) {
			return NaiveMultiplication(lhs, rhs);
		}

		size_t half_size = lhs.Rows() / 2;

		Matrix<T> A_11(half_size, half_size),
				  A_12(half_size, half_size),
				  A_21(half_size, half_size),
				  A_22(half_size, half_size),
				  B_11(half_size, half_size),
				  B_12(half_size, half_size),
				  B_21(half_size, half_size),
				  B_22(half_size, half_size);

		Split(lhs, A_11, A_12, A_21, A_22);
		Split(rhs, B_11, B_12, B_21, B_22);

		std::future<Matrix<T>> M_1_future = std::async(std::launch::async, StrassenMultiThread<T>, A_11 + A_22, B_11 + B_22, lower_border);
		std::future<Matrix<T>> M_2_future = std::async(std::launch::async, StrassenMultiThread<T>, A_21 + A_22, B_11, lower_border);
		std::future<Matrix<T>> M_3_future = std::async(std::launch::async, StrassenMultiThread<T>, A_11, B_12 - B_22, lower_border);

		M_1_future.wait();
		M_2_future.wait();
		M_3_future.wait();

		Matrix<T> M_1 = M_1_future.get();
		Matrix<T> M_2 = M_2_future.get();
		Matrix<T> M_3 = M_3_future.get();
		Matrix<T> M_4 = StrassenMultiThread(A_22, B_21 - B_11, lower_border);
		Matrix<T> M_5 = StrassenMultiThread(A_11 + A_12, B_22, lower_border);
		Matrix<T> M_6 = StrassenMultiThread(A_21 - A_11, B_11 + B_12, lower_border);
		Matrix<T> M_7 = StrassenMultiThread(A_12 - A_22, B_21 + B_22, lower_border);


		Matrix<T> result(lhs.Rows(), rhs.Columns());
		Merge(result, M_1 + M_4 - M_5 + M_7,
					  M_3 + M_5,
				      M_2 + M_4,
					  M_1 - M_2 + M_3 + M_6);

		return result;
	}

	template<typename T>
	Matrix<T> StrassenAlgorithm(const Matrix<T>& lhs, const Matrix<T>& rhs, size_t lower_border = 8, bool multithreaded = false) {
		if (lhs.Columns() != rhs.Rows() || lhs.Empty() || rhs.Empty()) {
			throw std::invalid_argument("Matrices have wrong dimensions");
		}

		size_t temp = lhs.Rows();

		while (!(temp & 1)) {
			temp = temp >> 1;
		}

		bool is_power_of_two_sqr_matrix = (temp == 1) && (lhs.Rows() == lhs.Columns());

		Matrix<T> result;
		if (is_power_of_two_sqr_matrix) {
			if (multithreaded) {
				result = StrassenMultiThread(lhs, rhs, lower_border);
			}
			else {
				result = StrassenSingleThread(lhs, rhs, lower_border);
			}
		}
		else {
			size_t upper_border = std::max({ lhs.Rows(), lhs.Columns(), rhs.Rows(), rhs.Columns() });
			size_t dimension = 1;

			while (dimension < upper_border) {
				dimension *= 2;
			}

			Matrix<T> new_lhs(dimension, dimension), new_rhs(dimension, dimension);
			for (size_t i = 0; i < lhs.Rows(); ++i) {
				for (size_t j = 0; j < lhs.Columns(); ++j) {
					new_lhs.At(i, j) = lhs.At(i, j);
				}
			}

			for (size_t i = 0; i < rhs.Rows(); ++i) {
				for (size_t j = 0; j < rhs.Columns(); ++j) {
					new_rhs.At(i, j) = rhs.At(i, j);
				}
			}

			if (multithreaded) {
				result = StrassenMultiThread(new_lhs, new_rhs, lower_border);
			}
			else {
				result = StrassenSingleThread(new_lhs, new_rhs, lower_border);
			}
		}

		result.Resize(lhs.Rows(), rhs.Columns());
		return result;
	}
}