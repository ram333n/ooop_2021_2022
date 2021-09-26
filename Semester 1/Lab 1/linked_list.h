#pragma once

template<typename T>
class LinkedList {

private:
	struct Node;
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;

public:	
	class Iterator {
	public:
		Iterator() : node_ptr(nullptr) {};
		Iterator(Node* other_node) : node_ptr(other_node) {};
		T& operator*() const {
			return node_ptr->value;
		}

		T* operator->() {
			return &node_ptr->value;
		}

		Iterator& operator++() {
			if (node_ptr) {
				node_ptr = node_ptr->next;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator next_it = *this;
			next_it++;
			return next_it;
		}

		Iterator& operator--() {
			if (node_ptr) {
				node_ptr = node_ptr->prev;
			}
			return *this;
		}

		Iterator operator--(int) {
			Iterator prev_it = *this;
			++*this;
			return prev_it;
		}

		bool operator==(const Iterator& other) {
			return node_ptr == other.node_ptr;
		}

		bool operator!=(const Iterator& other) {
			return node_ptr != other.node_ptr;
		}

		Node* node_ptr;
	};


	LinkedList() {};
	void PushBack(const T& new_value) {
		Node* to_push = new Node(new_value);
		if (!tail) {
			head = to_push;
		}
		else {
			tail->next = to_push;
		}

		tail = to_push;
		++size;
	}

	void PushFront(const T& new_value) {
		Node* to_push = new Node(new_value);
		if (!begin) {
			tail = to_push;
		}
		else {
			head->prev = to_push;
		}

		head = to_push;
		++size;
	}

	Iterator Insert(const T& new_value, Iterator pos_to_insert) {
		if (!pos_to_insert.node_ptr) {
			return Iterator();
		}

		Iterator result;
		if (!head) {
			PushFront(new_value);
			result(head);
		}
		else {
			Node* to_insert = new Node(new_value);
			pos_to_insert.node_ptr->prev->next = to_insert;
			to_insert->prev = pos_to_insert.node_ptr->prev;
			to_insert->next = pos_to_insert.node_ptr;
			pos_to_insert.node_ptr->prev = to_insert;
			result(to_insert);
		}

		++size;
		return result;
	}

	bool Empty() const {
		return head == nullptr;
	}

	size_t Size() const {
		return size;
	}

	void Remove(Iterator it) {
		if (!it.node_ptr) {
			return;
		}

		if (it.node_ptr->prev) {
			it.node_ptr->prev->next = it.node_ptr->next;
		}
		else {
			head = it.node_ptr->next;
		}

		if (it.node_ptr->next) {
			it.node_ptr->next->prev = it.node_ptr->prev;
		}
		else {
			tail = it.node_ptr->prev;
		}

		delete it.node_ptr;
		--size;
	}

	void PopBack() {
		Remove(Iterator(tail));
	}

	void PopFront() {
		Remove(Iterator(head));
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator();
	}

	const Iterator begin() const {
		return Iterator(head);
	}
	const Iterator end() const {
		return Iterator();
	}

	~LinkedList() {
		while (head) {
			PopFront();
		}
	}
};

template<typename T>
struct LinkedList<T>::Node {
	T value;
	Node* next, * prev;
	Node() : next(nullptr), prev(nullptr) {};
	Node(const T& new_value) : value(new_value), next(nullptr), prev(nullptr) {};
};

