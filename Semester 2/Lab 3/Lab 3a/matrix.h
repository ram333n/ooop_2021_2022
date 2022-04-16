#pragma once

#include <iostream>
#include <vector>
#include <type_traits>

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
		//Ctor from two iterators

		T& At(size_t row, size_t column);
		const T& At(size_t row, size_t column) const;

		size_t Rows() const;
		size_t Columns() const;

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
			row.resize(columns_count);
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
		if (lhs.rows_count != rhs.rows_count || lhs.columns_count != rhs.columns_count) {
			return false;
		}

		for (size_t i = 0; i < lhs.rows_count; ++i) {
			for (size_t j = 0; j < lhs.columns_count; ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}

		return true;
	}

	template<typename T>
	bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		return !(lhs == rhs);
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

		for (size_t i = 0; i < result.Rows(); ++i) {
			for (size_t j = 0; j < result.Columns(); ++j) {
				result.At(i,j) = 0;
				for (size_t k = 0; k < lhs.Columns(); ++k) {
					result.At(i, j) += lhs.At(i, k) * rhs.At(k, j);
				}
			}
		}

		return result;
	}

}