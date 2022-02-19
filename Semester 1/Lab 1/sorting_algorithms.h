#pragma once
#include "linked_list.h"
#include "array_list.h"
#include <list>
#include <utility>
#include <algorithm>

namespace Sort {
	template<typename Iterator, typename Comparator>
	void InsertionSort(Iterator range_begin, Iterator range_end, Comparator comparator) {
		using Type = typename Iterator::value_type;

		if (range_begin == range_end) {
			return;
		}

		Type to_insert;
		for (auto cur_item = std::next(range_begin); cur_item != range_end; ++cur_item) {
			to_insert = *cur_item;
			auto it = std::prev(cur_item);
			bool is_end = false;

			while (comparator(to_insert, *it)) {
				*std::next(it) = *it;
				if (it == range_begin) {
					is_end = true;
					break;
				}
				it--;
			}

			it = is_end ? range_begin : std::next(it);
			*it = to_insert;
		}
	}


	template <typename List, typename Iterator, typename Comparator>
	void MergeSort(Iterator range_begin, Iterator range_end, Comparator comparator) {
		int range_length = std::distance(range_begin, range_end);
		if (range_length < 2) {
			return;
		}

		List elements(range_begin, range_end);

		Iterator mid = std::next(elements.begin(), range_length / 2);
		MergeSort<List>(elements.begin(), mid, comparator);
		MergeSort<List>(mid, elements.end(), comparator);
		std::merge(elements.begin(), mid, mid, elements.end(), range_begin, comparator);
	}


	template<typename Iterator, typename Comparator>
	void QuickSort(Iterator range_begin, Iterator range_end, Comparator comparator) {
		if (range_begin != range_end) {
			auto pivot = *std::next(range_begin, std::distance(range_begin, range_end) / 2);

			auto first_border = std::partition(range_begin, range_end,
				[pivot, &comparator](const auto& lhs) {
					return comparator(lhs, pivot);
				});

			auto second_border = std::partition(first_border, range_end,
				[pivot, &comparator](const auto& rhs) {
					return !comparator(pivot, rhs);
				});

			QuickSort(range_begin, first_border, comparator);
			QuickSort(second_border, range_end, comparator);
		}
	}
}