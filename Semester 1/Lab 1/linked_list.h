#pragma once

template<typename T>
class LinkedList {
public:
	struct Node {
		T value;
		Node* next, * prev;
		Node() : next(nullptr), prev(nullptr) {};
		Node(const T& new_value) : value(new_value), next(nullptr), prev(nullptr) {};
	};

private:
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;

public:	
	LinkedList() {};

	void PushBack(const T& new_value) {
		Node* to_push = new Node(new_value);
		if (!tail) {
			head = to_push;
		}
		else {
			tail->next = to_push;
		}
		to_push->prev = tail;
		tail = to_push;
		++size;
	}

	void PushFront(const T& new_value) {
		Node* to_push = new Node(new_value);
		if (!head) {
			tail = to_push;
		}
		else {
			head->prev = to_push;
		}
		to_push->next = head;
		head = to_push;
		++size;
	}

	void Insert(const T& new_value, Node* pos_to_insert) {
		if (!pos_to_insert || !head) {
			return;
		}

		if (pos_to_insert == head) {
			PushFront(new_value);
		}
		else {
			Node* to_insert = new Node(new_value);
			pos_to_insert->prev->next = to_insert;
			to_insert->prev = pos_to_insert->prev;
			to_insert->next = pos_to_insert;
			pos_to_insert->prev = to_insert;
			++size;
		}
	}

	bool Empty() const {
		return head == nullptr;
	}

	size_t Size() const {
		return size;
	}

	void Remove(Node* to_remove) {
		if (!to_remove) {
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
		--size;
	}

	void PopBack() {
		Remove(tail);
	}

	void PopFront() {
		Remove(head);
	}

	Node* GetHead() {
		return head;
	}

	Node* GetTail() {
		return tail;
	}

	Node* Find(const T& to_find) {
		Node* current = GetHead();
		while(current&&current->value != to_find) {
			current = current->next;
		}

		return current;
	}

	~LinkedList() {
		while (head) {
			PopFront();
		}
	}
};



