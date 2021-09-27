#pragma once
#include <iostream>

template<typename T>
class ArrayList {
public:
	ArrayList() {};

	explicit ArrayList(size_t new_size)
		: data(new T[new_size]),
		  size(new_size),
		  capacity(new_size) {};

	T& operator[](size_t index);

	bool Empty() const;

	size_t Size() const;
	size_t Capacity() const;

	void Insert(T to_insert, int pos);
	void PushBack(T to_push);

	bool Remove(int to_remove);
	void PopBack();

	T* begin() const; //using pointers, as iterators 
	T* end() const;

	int Find(const T& to_find);

	~ArrayList();
private:
	void ResizeIfNecessary();

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};


template <typename T>
T& ArrayList<T>::operator[](size_t index) {
	return data[index];
}

template<typename T>
bool ArrayList<T>::Empty() const {
	return size == 0;
}

template<typename T>
size_t ArrayList<T>::Size() const {
	return size;
}

template<typename T>
size_t ArrayList<T>::Capacity() const {
	return capacity;
}

template<typename T>
void ArrayList<T>::Insert(T to_insert, int pos_to_insert) {
	if (pos_to_insert > static_cast<int>(size) || pos_to_insert < 0) {
		return;
	}

	if (pos_to_insert == size) {
		PushBack(to_insert);
	}
	else {
		ResizeIfNecessary();
		int current_pos = size - 1;
		while (current_pos >= pos_to_insert) {
			data[current_pos + 1] = std::move(data[current_pos]);
			current_pos--;
		}
		data[current_pos + 1] = std::move(to_insert);
		++size;
	}

}

template<typename T>
void ArrayList<T>::PushBack(T to_push) {
	ResizeIfNecessary();
	data[size++] = std::move(to_push);
}

template<typename T>
bool ArrayList<T>::Remove(int to_remove) {
	if (to_remove < 0 || to_remove >= static_cast<int>(size) ) {
		return false;
	}

	for (int i = to_remove; i + 1 < static_cast<int>(size); ++i) {
		data[i] = data[i + 1];
	}

	--size;
	return true;
}

template<typename T>
void ArrayList<T>::PopBack() {
	Remove(size - 1);
}

template<typename T>
T* ArrayList<T>::begin() const {
	return data;
}

template<typename T>
T* ArrayList<T>::end() const {
	return data + size;
}


template<typename T>
void ArrayList<T>::ResizeIfNecessary() {
	if (size >= capacity) {
		auto new_capacity = capacity == 0 ? 1 : 2 * capacity;
		T* new_data = new T[new_capacity];
		std::move(begin(), end(), new_data);
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
}

template<typename T>
int ArrayList<T>::Find(const T& to_find) {
	for (int i = 0; i < size; ++i) {
		if (data[i] == to_find) {
			return i;
		}
	}
	return -1;
}

template<typename T>
ArrayList<T>::~ArrayList() {
	delete[] data;
}