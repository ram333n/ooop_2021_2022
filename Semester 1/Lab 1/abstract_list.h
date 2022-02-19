#pragma once

namespace Lists {
	template<typename T, typename Iterator>
	class AbstractList {
	protected:
		size_t size_ = 0;
	public:
		virtual ~AbstractList() = default;

		bool Empty() const {
			return size_ == 0;
		}
		size_t Size() const {
			return size_;
		}

		virtual void PushBack(T to_insert) = 0;
		virtual void Insert(T to_insert, Iterator pos) = 0;

		virtual void Remove(Iterator pos) = 0;
		virtual void PopBack() = 0;

		virtual Iterator begin() = 0;
		virtual Iterator end() = 0;

		virtual const Iterator begin() const = 0;
		virtual const Iterator end() const = 0;
	};
}