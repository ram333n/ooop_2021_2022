#pragma once
#include <iostream>
#include "abstract_list.h"

namespace Lists {
	template<typename T>
	class ArrayListIterator : public std::iterator<std::random_access_iterator_tag, T> {
	protected:
		T* ptr_;
		ArrayListIterator(T* ptr) : ptr_(ptr) {}

		template <typename Type>
		friend class ArrayList;
	public:
		ArrayListIterator() : ptr_(nullptr) {}
		ArrayListIterator(const ArrayListIterator& it) : ptr_(it.ptr_) {}

		//Comparators

		bool operator<(ArrayListIterator rhs) const {
			return ptr_ < rhs.ptr_;
		}

		bool operator>(ArrayListIterator rhs) const {
			return ptr_ > rhs.ptr_;
		}

		bool operator<=(ArrayListIterator rhs) const {
			return ptr_ <= rhs.ptr_;
		}

		bool operator>=(ArrayListIterator rhs) const {
			return ptr_ >= rhs.ptr_;
		}

		bool operator==(ArrayListIterator rhs) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator!=(ArrayListIterator rhs) const {
			return ptr_ != rhs.ptr_;
		}

		//Assign and access operators

		ArrayListIterator& operator=(ArrayListIterator rhs) {
			ptr_ = rhs.ptr_;
			return *this;
		}

		ArrayListIterator& operator+=(ptrdiff_t diff) {
			ptr_ += diff;
			return *this;
		}

		ArrayListIterator& operator-=(ptrdiff_t diff) {
			ptr_ -= diff;
			return *this;
		}

		T& operator*() const {
			return *ptr_;
		}

		T& operator[](size_t index) {
			return ptr_[index];
		}

		const T& operator[](size_t index) const {
			return ptr_[index];
		}

		T* operator->() {
			return ptr_;
		}

		const T* operator->() const {
			return ptr_;
		}

		//Arithmetic operators

		ArrayListIterator& operator++() {
			++ptr_;
			return *this;
		}

		ArrayListIterator& operator--() {
			--ptr_;
			return *this;
		}

		ArrayListIterator operator++(int) {
			ArrayListIterator temp(*this);
			++ptr_;
			return temp;
		}

		ArrayListIterator operator--(int) {
			ArrayListIterator temp(*this);
			--ptr_;
			return temp;
		}

		ptrdiff_t operator-(ArrayListIterator rhs) const {
			return ptr_ - rhs.ptr_;
		}

		ArrayListIterator operator+(ptrdiff_t diff) const {
			return ArrayListIterator(ptr_ + diff);
		}

		ArrayListIterator operator-(ptrdiff_t diff) const {
			return ArrayListIterator(ptr_ - diff);
		}
	};

	template<typename T>
	class ArrayList : public AbstractList<T, ArrayListIterator<T>> {
	private:
		T* data_ = nullptr;
		size_t capacity_ = 0;
	public:
		ArrayList() {};

		explicit ArrayList(size_t new_size)
			: data_(new T[new_size]),
			capacity_(new_size) 
		{
			this->size_ = new_size;
		};

		T& operator[](size_t index) {
			return data_[index];
		}
		
		const T& operator[](size_t index) const {
			return data_[index];
		}

		size_t Capacity() const {
			return capacity_;
		}

		void Insert(T to_insert, ArrayListIterator<T> pos) override {
			if (pos < begin() || pos > end()) {
				return;
			}

			if (end() == pos) {
				PushBack(to_insert);
			}
			else {
				int diff = pos - begin();
				ResizeIfNecessary(); //possible invalidation of iterators
				pos = begin() + diff;
				ArrayListIterator<T> current_pos = begin() + this->size_ - 1;
				while (current_pos >= pos) {
					*(current_pos + 1) = std::move(*current_pos);
					--current_pos;
				}
				*(current_pos + 1) = std::move(to_insert);
				++this->size_;
			}
		};

		void PushBack(T to_push) override {
			ResizeIfNecessary();
			data_[this->size_++] = std::move(to_push);
		}

		void Remove(ArrayListIterator<T> pos) override {
			if (pos < begin() || pos >= end()) {
				return;
			}

			for (auto it = pos; it + 1 < end(); ++it) {
				*it = std::move(*(it + 1));
			}

			--this->size_;
		};

		void PopBack() override {
			Remove(end() - 1);
		}

		ArrayListIterator<T> begin() override {
			return ArrayListIterator<T>(data_);
		}

		ArrayListIterator<T> end() override {
			return ArrayListIterator<T>(data_ + this->size_);
		};

		const ArrayListIterator<T> begin() const override {
			return ArrayListIterator<T>(data_);
		}

		const ArrayListIterator<T> end() const override {
			return ArrayListIterator<T>(data_ + this->size_);
		}

		~ArrayList() {
			delete[] data_;
		}
	private:
		void ResizeIfNecessary() {
			if (this->size_ >= capacity_) {
				size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
				T* new_data = new T[new_capacity];
				std::move(begin(), end(), new_data);
				delete[] data_;
				data_ = new_data;
				capacity_ = new_capacity;
			}
		}
	};
}