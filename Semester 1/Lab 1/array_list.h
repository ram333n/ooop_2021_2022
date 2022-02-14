#pragma once
#include <iostream>

namespace Lists {
	template<typename T>
	class ArrayList {
	public:
		class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
		protected:
			T* ptr_;
			Iterator(T* ptr) : ptr_(ptr) {}
			friend class ArrayList;
		public:
			Iterator() : ptr_(nullptr) {}
			Iterator(const Iterator& it) : ptr_(it.ptr_) {}

			//Comparators

			bool operator<(Iterator rhs) const {
				return ptr_ < rhs.ptr_;
			}

			bool operator>(Iterator rhs) const {
				return ptr_ > rhs.ptr_;
			}

			bool operator<=(Iterator rhs) const {
				return ptr_ <= rhs.ptr_;
			}

			bool operator>=(Iterator rhs) const {
				return ptr_ >= rhs.ptr_;
			}

			bool operator==(Iterator rhs) const {
				return ptr_ == rhs.ptr_;
			}

			bool operator!=(Iterator rhs) const {
				return ptr_ != rhs.ptr_;
			}

			//Assign and access operators

			Iterator& operator=(Iterator rhs) {
				ptr_ = rhs.ptr_;
				return *this;
			}

			Iterator& operator+=(ptrdiff_t diff) {
				ptr_ += diff;
				return *this;
			}

			Iterator& operator-=(ptrdiff_t diff) {
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

			Iterator& operator++() {
				++ptr_;
				return *this;
			}

			Iterator& operator--() {
				--ptr_;
				return *this;
			}

			Iterator operator++(int) {
				Iterator temp(*this);
				++ptr_;
				return temp;
			}

			Iterator operator--(int) {
				Iterator temp(*this);
				--ptr_;
				return temp;
			}

			ptrdiff_t operator-(Iterator rhs) const {
				return ptr_ - rhs.ptr_;
			}

			Iterator operator+(ptrdiff_t diff) const {
				return Iterator(ptr_ + diff);
			}

			Iterator operator-(ptrdiff_t diff) const {
				return Iterator(ptr_ - diff);
			}
		};

		ArrayList() {};

		explicit ArrayList(size_t new_size)
			: data_(new T[new_size]),
			size_(new_size),
			capacity_(new_size) {};

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		bool Empty() const;

		size_t Size() const;
		size_t Capacity() const;

		void Insert(T to_insert, Iterator pos);
		void PushBack(T to_push);

		void Remove(Iterator pos);
		void PopBack();

		auto begin();
		auto end();

		const auto begin() const;
		const auto end() const;

		~ArrayList();
	private:
		void ResizeIfNecessary();

		T* data_ = nullptr;
		size_t size_ = 0;
		size_t capacity_ = 0;
	};
	
	template <typename T>
	T& ArrayList<T>::operator[](size_t index) {
		return data_[index];
	}

	template <typename T>
	const T& ArrayList<T>::operator[](size_t index) const {
		return data_[index];
	}

	template<typename T>
	bool ArrayList<T>::Empty() const {
		return size_ == 0;
	}

	template<typename T>
	size_t ArrayList<T>::Size() const {
		return size_;
	}

	template<typename T>
	size_t ArrayList<T>::Capacity() const {
		return capacity_;
	}

	template<typename T>
	void ArrayList<T>::Insert(T to_insert, Iterator pos) {
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
			Iterator current_pos = begin() + size_ - 1;
			while (current_pos >= pos) {
				*(current_pos + 1) = std::move(*current_pos);
				--current_pos;
			}
			*(current_pos + 1) = std::move(to_insert);
			++size_;
		}

	}

	template<typename T>
	void ArrayList<T>::PushBack(T to_push) {
		ResizeIfNecessary();
		data_[size_++] = std::move(to_push);
	}

	template<typename T>
	void ArrayList<T>::Remove(Iterator pos) {
		if (pos < begin() || pos >= end()) {
			return;
		}

		for (auto it = pos; it + 1 < end(); ++it) {
			*it = std::move(*(it + 1));
		}

		--size_;
	}

	template<typename T>
	void ArrayList<T>::PopBack() {
		Remove(size_ - 1);
	}

	template<typename T>
	auto ArrayList<T>::begin() {
		return Iterator(data_);
	}

	template<typename T>
	auto ArrayList<T>::end() {
		return Iterator(data_ + size_);
	}

	template<typename T>
	const auto ArrayList<T>::begin() const {
		return Iterator(data_);
	}

	template<typename T>
	const auto ArrayList<T>::end() const {
		return Iterator(data_ + size_);
	}


	template<typename T>
	void ArrayList<T>::ResizeIfNecessary() {
		if (size_ >= capacity_) {
			size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
			T* new_data = new T[new_capacity];
			std::move(begin(), end(), new_data);
			delete[] data_;
			data_ = new_data;
			capacity_ = new_capacity;
		}
	}

	template<typename T>
	ArrayList<T>::~ArrayList() {
		delete[] data_;
	}
}