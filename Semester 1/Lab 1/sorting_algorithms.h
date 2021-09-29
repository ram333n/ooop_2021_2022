#pragma once
#include "linked_list.h"
#include "array_list.h"
#include <list>
#include <utility>
#include <algorithm>

template<typename T,typename Comparator>
void InsertionSort(ArrayList<T>& array_list, Comparator comparator) {
	T to_insert;
	for (int i = 1; i < static_cast<int>(array_list.Size()); ++i) {
		to_insert = array_list[i];
		int j = i - 1;

		while (j > -1 && comparator(to_insert, array_list[j])) {
			array_list[j + 1] = array_list[j];
			j--;
		}

		array_list[j + 1] = to_insert;
	}
}

template<typename T, typename Comparator>
int Partition(ArrayList<T>& array_list, int low, int high, Comparator comparator) {
	T pivot = array_list[high];
	int i = low - 1;

	for (int j = low; j < high; ++j) {
		if (comparator(array_list[j], pivot)) {
			i++;
			std::swap(array_list[i], array_list[j]);
		}
	}
	std::swap(array_list[i+1],array_list[high]);
	return i + 1;
}

template<typename T,typename Comparator>
void QuickSort(ArrayList<T>& array_list, int low, int high, Comparator comparator) {
	if (low >= high) {
		return;
	}

	int partitioning_index = Partition(array_list, low, high, comparator);
	QuickSort(array_list, low, partitioning_index - 1, comparator);
	QuickSort(array_list, partitioning_index + 1, high, comparator);
}

template<typename T, typename Comparator>
void MergeSort(T* range_begin, T* range_end, Comparator comparator) {
	int range_length = range_end - range_begin;
	if (range_length < 2) {
		return;
	}

	ArrayList<T> elements(range_length);
	for (int i = 0; i < range_length; ++i) {
		elements[i] = *(range_begin + i);
	}

	auto mid = elements.begin() + range_length / 2;
	MergeSort(elements.begin(), mid, comparator);
	MergeSort(mid, elements.end(), comparator);
	std::merge(elements.begin(), mid, mid, elements.end(), range_begin, comparator);
}

template<typename T, typename Comparator>
bool IsSorted(const LinkedList<T>& linked_list, Comparator comparator) {
	if (linked_list.Size() < 2) {
		return true;
	}

	Node<T>* current = linked_list.GetHead();
	while (current->next) {
		if (comparator(current->value, current->next->value)|| current->value == current->next->value) {
			current = current->next;
		}
		else {
			break;
		}
	}

	return current == linked_list.GetTail();
}

template<typename T, typename Comparator>
void InsertionSort(LinkedList<T>& linked_list, Comparator comparator) {
	Node<T>* current = linked_list.GetHead();
	Node<T>* to_insert = nullptr;

	while (current) {
		to_insert = current->next;
		while (to_insert &&
			   to_insert->prev &&
			   comparator(to_insert->value, to_insert->prev->value))
		{
			std::swap(to_insert->value, to_insert->prev->value);
			to_insert = to_insert->prev;
		}
		current = current->next;
	}
}

template<typename T, typename Comparator>
Node<T>* Partition(Node<T>* low, Node<T>* high,Comparator comparator) {
	Node<T>* current = low;
	Node<T>* location = low->prev;

	while (current && current != high) {
		if (comparator(current->value, high->value) || current->value == high->value) {
			if (location) {
				location = location->next;
			}
			else {
				location = low;
			}
			std::swap(current->value, location->value);
		}
		current = current->next;
	}

	if (!location) {
		location = low;
	}
	else {
		location = location->next;
	}
	std::swap(high->value, location->value);
	return location;
}
	

template<typename T, typename Comparator>
void QuickSort(Node<T>* low, Node<T>* high, Comparator comparator) {
	if (low != high && low && high && high->next != low) {
		Node<T>* partitioning_node = Partition(low, high, comparator);

		if (partitioning_node) {
			QuickSort(partitioning_node->next, high, comparator);
			QuickSort(low, partitioning_node->prev, comparator);
		}
	}
}

template<typename T, typename Comparator>
Node<T>* Merge(Node<T>* first, Node<T>* second, Comparator comparator) {
	if (!first) {
		return second;
	}

	if (!second) {
		return first;
	}

	if (comparator(first->value, second->value)) {
		first->next = Merge(first->next, second, comparator);
		first->next->prev = first;
		first->prev = nullptr;
		return first;
	}
	else {
		second->next = Merge(first, second->next, comparator);
		second->next->prev = second;
		second->prev = nullptr;
		return second;
	}
}

template<typename T>
Node<T>* Split(Node<T>* head) {
	Node<T>* fast = head;
	Node<T>* slow = head;
	while (fast->next && fast->next->next){
		fast = fast->next->next;
		slow = slow->next;
	}
	Node<T>* temp = slow->next;
	slow->next = nullptr;
	return temp;
}

template<typename T, typename Comparator>
Node<T>* MergeSortImpl(Node<T>* head, Comparator comparator){
	if (!head || !head->next) {
		return head;
	}
	Node<T>* second = Split(head);

	head = MergeSortImpl(head, comparator);
	second = MergeSortImpl(second, comparator);

	return Merge(head, second, comparator);
}

template<typename T, typename Comparator>
void MergeSort(LinkedList<T>& linked_list, Comparator comparator) {
	linked_list = LinkedList<T>(MergeSortImpl(linked_list.GetHead(), comparator));
}


template<typename Iterator, typename Comparator>
void QuickSort(Iterator low, Iterator high, Comparator comparator) {
	if (low != high) {
		auto pivot = *std::next(low, std::distance(low, high) / 2);

		auto first_border = std::partition(low, high,
			[pivot, &comparator](const auto& lhs) {
				return comparator(lhs, pivot);
			});

		auto second_border = std::partition(first_border, high,
			[pivot, &comparator](const auto& rhs) {
				return !comparator(pivot, rhs);
			});

		QuickSort(low, first_border, comparator);
		QuickSort(second_border, high, comparator);
	}
}

template<typename Iterator, typename Comparator>
void MergeSort(Iterator range_begin, Iterator range_end, Comparator comparator) {
	int range_length = std::distance(range_begin, range_end);
	if (range_length < 2) {
		return;
	}

	std::list<typename Iterator::value_type> elements(range_begin, range_end);

	auto mid = std::next(elements.begin(), range_length / 2);
	MergeSort(elements.begin(), mid, comparator);
	MergeSort(mid, elements.end(), comparator);
	std::merge(elements.begin(), mid, mid, elements.end(), range_begin, comparator);
}
