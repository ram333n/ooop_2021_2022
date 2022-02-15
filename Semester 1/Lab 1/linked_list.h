#pragma once
#include <iostream>

template<typename T>
struct Node {
	T value;
	Node* next, * prev;
	Node() : next(nullptr), prev(nullptr) {};
	Node(T new_value) : value(std::move(new_value)), next(nullptr), prev(nullptr) {};
};

template<typename T>
class LinkedList {	
private:
	size_t size_ = 0;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;

public:	
	LinkedList() {};
	LinkedList(Node<T>* new_head);

	void PushBack(T new_value);
	void PushFront(T new_value);
	void Insert(T new_value, Node<T>* pos_to_insert);

	bool Empty() const;
	size_t Size() const;

	void Remove(Node<T>* to_remove);
	void PopBack();
	void PopFront();

	Node<T>* GetHead() const ;
	Node<T>* GetTail() const ;
	Node<T>* Find(const T& to_find);

	~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList(Node<T>* new_head) {
	if (!new_head) {
		size_ = 1;
		head = new_head;
		while (new_head->next) {
			new_head = new_head->next;
			++size_;
		}
		tail = new_head;
	}
};

template<typename T>
void LinkedList<T>::PushBack(T new_value) {
	Node<T>* to_push = new Node<T>(std::move(new_value));
	if (!tail) {
		head = to_push;
	}
	else {
		tail->next = to_push;
	}
	to_push->prev = tail;
	tail = to_push;
	++size_;
}

template<typename T>
void LinkedList<T>::PushFront(T new_value) {
	Node<T>* to_push = new Node<T>(std::move(new_value));
	if (!head) {
		tail = to_push;
	}
	else {
		head->prev = to_push;
	}
	to_push->next = head;
	head = to_push;
	++size_;
}

template<typename T>
void LinkedList<T>::Insert(T new_value, Node<T>* pos_to_insert) {
	if (!pos_to_insert || !head) {
		return;
	}

	if (pos_to_insert == head) {
		PushFront(new_value);
	}
	else {
		Node<T>* to_insert = new Node<T>(std::move(new_value));
		pos_to_insert->prev->next = to_insert;
		to_insert->prev = pos_to_insert->prev;
		to_insert->next = pos_to_insert;
		pos_to_insert->prev = to_insert;
		++size_;
	}
}

template<typename T>
bool LinkedList<T>::Empty() const {
	return head == nullptr;
}

template<typename T>
size_t LinkedList<T>::Size() const {
	return size_;
}

template<typename T>
void LinkedList<T>::Remove(Node<T>* to_remove) {
	if (!to_remove||!head) {
		return;
	}

	if (to_remove->prev) {
		to_remove->prev->next = to_remove->next;
	}
	else {
		head = to_remove->next;
	}

	if (to_remove->next) {
		to_remove->next->prev = to_remove->prev;
	}
	else {
		tail = to_remove->prev;
	}

	delete to_remove;
	--size_;
}

template<typename T>
void LinkedList<T>::PopBack() {
	Remove(tail);
}

template<typename T>
void LinkedList<T>::PopFront() {
	Remove(head);
}

template<typename T>
Node<T>* LinkedList<T>::GetHead() const {
	return head;
}

template<typename T>
Node<T>* LinkedList<T>::GetTail() const {
	return tail;
}

template<typename T>
Node<T>* LinkedList<T>::Find(const T& to_find) {
	Node<T>* current = GetHead();
	while (current && current->value != to_find) {
		current = current->next;
	}
	return current;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	while (head) {
		PopFront();
	}
}