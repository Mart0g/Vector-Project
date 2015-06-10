#pragma once

#include <iostream>
#include <typeinfo>

template <typename T>
class Vector
{
private:
	int v_size;
	int v_capacity;
	T * dataArr;

	void copy(T**, int);

public:
	Vector();
	Vector(int);
	Vector(const Vector<T>&);
	~Vector();

	int size();
	int capacity();

	void push_back(const T&);
	void pop_back();
	void insert(int, T);
	void erase(int);
	void clear();
	bool empty();

	T& back();
	T& front();

	Vector<T>& operator=(const Vector<T>&);
	T& operator[](int);

	void resize(int);
	void shrink_to_fit();
	void swap(Vector<T>&);
	size_t max_size() const;
};

template <typename T>
Vector<T>::Vector() {
	v_capacity = 4;
	v_size = 0;
	dataArr = new T[v_capacity];
}

template<typename T>
Vector<T>::Vector(int v) {
	if (v >= 1) {
		v_capacity = v;
		v_size = v;
		dataArr = new T[v];
	}
	else {
		throw std::invalid_argument("Invalid capacity !");
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v) {
	v_size = v.v_size;
	v_capacity = v.v_capacity;
	dataArr = new T[v_capacity];
	copy(&dataArr, v_size);
}

template<typename T>
Vector<T>::~Vector() {
	delete[] dataArr;
}

template<typename T>
T& Vector<T>::front() {
	if (empty()) {
		throw std::out_of_range("The vector is empty !");
	}
	else {
		return dataArr[0];
	}
}

template<typename T>
T& Vector<T>::back() {
	if (empty()) {
		throw std::out_of_range("The vector is empty !");
	}
	else {
		return dataArr[v_size - 1];
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> & v) {
	delete[] dataArr;
	v_size = v.v_size;
	v_capacity = v.v_capacity;
	dataArr = new T[v_capacity];
	for (int i = 0; i < v_size; i++) {
		dataArr[i] = v.dataArr[i];
	}
	return *this;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	return dataArr[index];
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (v_capacity == v_size) {
		v_capacity *= 2;
		copy(&dataArr, v_size);
	}
	dataArr[v_size] = value;
	v_size++;
}

template<typename T>
void Vector<T>::pop_back() {
	if (!empty()) {
		shrink_to_fit();
		copy(&dataArr, v_size);
		v_size--;
	}
	else {
		throw std::out_of_range("The vector is out of range !");
	}
}

template<typename T>
void Vector<T>::insert(int index, T value) {
	if (v_capacity > index) {
		if (v_size > index) {
			if (v_size == v_capacity) {
				v_capacity *= 2;
			}
			v_size++;
			T *temp = new T[v_capacity];

			if (index != 0) {
				int i = 0;
				for (i; i < index; i++) {
					temp[i] = dataArr[i];
				}
			}
			temp[index] = value;
			int i = index + 1;
			for (i; i < v_size; i++) {
				temp[i] = dataArr[i - 1];
			}

			delete[] dataArr;
			dataArr = temp;
		}
		else {
			dataArr[index] = value;
			v_size = index;
		}
	}
	else {
		v_capacity *= 2;
		copy(&dataArr, v_size);
		insert(index, value);
	}
}

template<typename T>
void Vector<T>::erase(int index) {
	if (v_capacity > index) {
		T *temp = new T[v_capacity];
		int i = 0;
		for (i; i < index; i++) {
			temp[i] = dataArr[i];
		}
		i = index + 1;
		for (i; i < v_size; i++) {
			temp[i - 1] = dataArr[i];
		}
		delete[] dataArr;
		dataArr = temp;
		shrink_to_fit();
		v_size--;
	}
}

template<typename T>
void Vector<T>::resize(int newSize) {
	if (newSize > v_capacity) {
		v_capacity *= 2;
		copy(&dataArr, v_size);
	}
	int i = newSize - (newSize - v_size);
	v_size = newSize;
	string type = typeid(dataArr[0]).name();
	T temp;
	if (type.find("string") != -1) {
		temp = T("0");
	}
	else {
		temp = T(0);
	}
	for (i; i < newSize; i++) {
		dataArr[i] = temp;
	}
}

template<typename T>
void Vector<T>::shrink_to_fit() {
	if (((double)(v_size + 1) / v_capacity) < 0.25) {
		v_capacity /= 2;
	}
}

template<typename T>
size_t Vector<T>::max_size() const {
	return size_t(-1) / sizeof(T);
}

template<typename T>
int Vector<T>::size() {
	return v_size;
}

template<typename T>
int Vector<T>::capacity() {
	return v_capacity;
}

template<typename T>
void Vector<T>::swap(Vector<T> & v) {
	Vector <T> * temp = new Vector<T>();
	*temp = *this;
	*this = v;
	v = *temp;
}

template<typename T>
bool Vector<T>::empty() {
	if (v_size == 0) {
		return true;
	}
	return false;
}

template<typename T>
void Vector<T>::clear() {
	v_capacity = 4;
	v_size = 0;
	dataArr = new T[4];
}

template<typename T>
void Vector<T>::copy(T **arr, int end) {
	T *temp = new T[v_capacity];
	int i = 0;
	for (i; i < end; i++) {
		temp[i] = (*arr)[i];
	}
	delete[] * arr;
	*arr = temp;
}
