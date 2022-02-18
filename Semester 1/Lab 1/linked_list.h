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
			if (ptr_) {
				ptr_ = ptr_->next;
			}
			return *this;
		}

		LinkedListIterator& operator--() {
			if (ptr_) {
				ptr_ = ptr_->prev;
			}
			return *this;
		}

		LinkedListIterator operator++(int) {
			LinkedListIterator temp(*this);
			if (ptr_) {
				ptr_ = ptr_->next;
			}
			return temp;
		}

		LinkedListIterator operator--(int) {
			LinkedListIterator temp(*this);
			if (ptr_) {
				ptr_ = ptr_->prev;
			}
			return temp;
		}
	};


	template<typename T>
	class LinkedList : public AbstractList<T, LinkedListIterator<T>> {
	private:
		Node<T>* head_ = nullptr;
		Node<T>* tail_ = nullptr;
	public:
		LinkedList() {};

		void Insert(T to_insert, LinkedListIterator<T> pos) override {
			if (!head_) {
				return;
			}

			if (!pos.ptr_) {
				PushBack(to_insert);
			}
			else if (pos.ptr_ == head_) {
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
			if (!tail_) {
				head_ = node_to_push;
			}
			else {
				tail_->next = node_to_push;
			}
			node_to_push->prev = tail_;
			tail_ = node_to_push;

			++this->size_;
		}

		void PushFront(T to_insert) {
			Node<T>* node_to_push = new Node<T>(std::move(to_insert));
			if (!head_) {
				tail_ = node_to_push;
			}
			else {
				head_->prev = node_to_push;
			}
			node_to_push->next = head_;
			head_ = node_to_push;
			++this->size_;
		}

		void Remove(LinkedListIterator<T> pos) override {
			if (!pos.ptr_ || !head_ ) {
				return;
			}

			if (pos.ptr_->prev) {
				pos.ptr_->prev->next = pos.ptr_->next;
			}
			else {
				head_ =  pos.ptr_->next;
			}

			if (pos.ptr_->next) {
				pos.ptr_->next->prev = pos.ptr_->prev;
			}
			else {
				tail_ = pos.ptr_->prev;
			}

			delete pos.ptr_;
			--this->size_;
		};

		void PopBack() override {
			Remove(LinkedListIterator<T>(tail_));
		}

		void PopFront() {
			Remove(LinkedListIterator<T>(head_));
		};

		LinkedListIterator<T> begin() override {
			return LinkedListIterator<T>(head_);
		}

		LinkedListIterator<T> end() override {
			return LinkedListIterator<T>();
		}

		const LinkedListIterator<T> begin() const override {
			return LinkedListIterator<T>(head_);
		}

		const LinkedListIterator<T> end() const override {
			return LinkedListIterator<T>();
		}

		~LinkedList() {
			while (head_) {
				PopFront();
			}
		}
	};
}