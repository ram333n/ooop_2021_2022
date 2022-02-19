#pragma once
#include <iostream>
#include "abstract_list.h"

namespace Lists {
	template<typename T>
	struct Node {
		T value;
		Node* next, * prev;
		Node() : next(nullptr), prev(nullptr) {};
		Node(T new_value) : value(std::move(new_value)), next(nullptr), prev(nullptr) {};
	};

	template<typename T>
	class LinkedListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	private:
		Node<T>* ptr_;
		LinkedListIterator(Node<T>* ptr) : ptr_(ptr) {}

		template <typename Type>
		friend class LinkedList;
	public:
		LinkedListIterator() : ptr_(nullptr) {}
		LinkedListIterator(const LinkedListIterator& it) : ptr_(it.ptr_) {}

		//Comparators

		bool operator==(LinkedListIterator rhs) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator!=(LinkedListIterator rhs) const {
			return ptr_ != rhs.ptr_;
		}

		//Assign and access operators

		LinkedListIterator& operator=(const LinkedListIterator& rhs) {
			ptr_ = rhs.ptr_;
			return *this;
		}

		T& operator*() const {
			return ptr_->value;
		}

		T* operator->() {
			return &ptr_->value;
		}

		const T* operator->() const {
			return &ptr_->value;
		}

		//Increment and decrement operators

		LinkedListIterator& operator++() {
			ptr_ = ptr_->next;
			return *this;
		}

		LinkedListIterator& operator--() {
			ptr_ = ptr_->prev;
			return *this;
		}

		LinkedListIterator operator++(int) {
			LinkedListIterator temp(*this);
			ptr_ = ptr_->next;
			return temp;
		}

		LinkedListIterator operator--(int) {
			LinkedListIterator temp(*this);
			ptr_ = ptr_->prev;
			return temp;
		}
	};


	template<typename T>
	class LinkedList : public AbstractList<T, LinkedListIterator<T>> {
	private:
		Node<T>* sentinel_;
	public:
		LinkedList() {
			sentinel_ = new Node<T>(T());
			sentinel_->prev = sentinel_;
			sentinel_->next = sentinel_;
		};

		explicit LinkedList(size_t new_size, T value = T()){
			sentinel_ = new Node<T>(T());
			sentinel_->prev = sentinel_;
			sentinel_->next = sentinel_;

			this->size_ = new_size;
			for (size_t i = 0; i < new_size; ++i) {			
				PushBack(value);
			}
		}

		LinkedList(LinkedListIterator<T> range_begin, LinkedListIterator<T> range_end) {
			sentinel_ = new Node<T>(T());
			sentinel_->prev = sentinel_;
			sentinel_->next = sentinel_;

			while (range_begin != range_end) {
				PushBack(*range_begin++);
				++this->size_;
			}
		}

		void Insert(T to_insert, LinkedListIterator<T> pos) override {
			if (pos.ptr_== sentinel_) {
				PushBack(to_insert);
			}
			else if (pos.ptr_ == sentinel_->next) {
				PushFront(to_insert);
			}
			else {
				Node<T>* node_to_insert = new Node<T>(std::move(to_insert));
				pos.ptr_->prev->next = node_to_insert;
				node_to_insert->prev = pos.ptr_->prev;
				node_to_insert->next = pos.ptr_;
				pos.ptr_->prev = node_to_insert;
				++this->size_;
			}
		}

		void PushBack(T to_insert) override {
			Node<T>* node_to_push = new Node<T>(std::move(to_insert));
			node_to_push->prev = sentinel_->prev;
			node_to_push->next = sentinel_;
			sentinel_->prev->next = node_to_push;
			sentinel_->prev = node_to_push;
			++this->size_;
		}

		void PushFront(T to_insert) {
			Node<T>* node_to_push = new Node<T>(std::move(to_insert));
			node_to_push->prev = sentinel_;
			node_to_push->next = sentinel_->next;
			sentinel_->next->prev = node_to_push;
			sentinel_->next = node_to_push;
			++this->size_;
		}

		void Remove(LinkedListIterator<T> pos) override {
			if (pos.ptr_ == sentinel_){
				return;
			}

			if (pos.ptr_ == sentinel_->next) {
				PopFront();
			}
			else if (pos.ptr_ == sentinel_->prev) {
				PopBack();
			}
			else {
				pos.ptr_->prev->next = pos.ptr_->next;
				pos.ptr_->next->prev = pos.ptr_->prev;
				delete pos.ptr_;
				--this->size_;
			}
		};

		void PopBack() override {
			if (sentinel_->prev == sentinel_) {
				return;
			}
			Node<T>* to_delete = sentinel_->prev;
			sentinel_->prev = sentinel_->prev->prev;
			sentinel_->prev->next = sentinel_;
			delete to_delete;
			--this->size_;
		}

		void PopFront() {
			if (sentinel_->next == sentinel_) {
				return;
			}
			Node<T>* to_delete = sentinel_->next;
			sentinel_->next = sentinel_->next->next;
			sentinel_->next->prev = sentinel_;
			delete to_delete;
			--this->size_;
		};

		LinkedListIterator<T> begin() override {
			return LinkedListIterator<T>(sentinel_->next);
		}

		LinkedListIterator<T> end() override {
			return LinkedListIterator<T>(sentinel_);
		}

		const LinkedListIterator<T> begin() const override {
			return LinkedListIterator<T>(sentinel_->next);
		}

		const LinkedListIterator<T> end() const override {
			return LinkedListIterator<T>(sentinel_);
		}

		~LinkedList() {
			while (sentinel_->next != sentinel_) {
				PopFront();
			}
			delete sentinel_;
		}
	};
	
	template <typename T>
	class StlList : public std::list<T> {
		using std::list<T>::list;

		size_t Size() const {
			return this->size();
		}
	};

}