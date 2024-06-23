#pragma once
#include <iostream>
namespace
{
	const size_t DEFAULT_CAP = 8;
}
template <typename T>
class MyVector
{
	T* _data;
	size_t _size = 0;
	size_t _capacity = DEFAULT_CAP;

	void copyFrom(const MyVector<T>& other);
	void free();
	void moveFrom(MyVector<T>&& other);
	void resize(size_t newCap);

public:
	MyVector();
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other) noexcept;
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other) noexcept;
	~MyVector<T>();

	size_t size() const;
	size_t capacity() const;

	void push_back(const T& data);
	void push_back(T&& data);
	void pop_back();
	void insert(const T& data, unsigned idx);
	void insert(T&& data, unsigned idx);
	void erase(unsigned idx);
	void clear();

	bool empty() const;
	T& operator[](const size_t idx);
	const T& operator[](const size_t idx) const;

};
template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = new T[_capacity];
	for (size_t i = 0; i < _size; i++)
		_data[i] = other._data[i];
}

template <typename T>
void MyVector<T>::free()
{
	delete[] _data;
	_data = nullptr;
	_capacity = _size = 0;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;
	other._data = nullptr;
	other._capacity = other._size = 0;
}

template <typename T>
void MyVector<T>::resize(size_t newCap)
{
	_capacity = newCap;
	T* temp = new T[newCap];
	for (size_t i = 0; i < _size; i++)
		temp[i] = std::move(_data[i]);
	delete[] _data;
	_data = temp;
}

template <typename T>
MyVector<T>::MyVector()
{
	_data = nullptr;
	_size = _capacity = 0;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector<T>()
{
	free();
}

template <typename T>
size_t MyVector<T>::size() const
{
	return _size;
}

template <typename T>
size_t MyVector<T>::capacity() const
{
	return _capacity;
}

template <typename T>
void MyVector<T>::push_back(const T& data)
{
	if (_capacity == 0)
		resize(DEFAULT_CAP);
	else if (_size == _capacity)
		resize(2 * _capacity);
	_data[_size++] = data;
}

template <typename T>
void MyVector<T>::push_back(T&& data)
{
	if (_capacity == 0)
		resize(DEFAULT_CAP);
	if (_size == _capacity)
		resize(2 * _capacity);
	_data[_size++] = std::move(data);
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (empty())
		throw "Empty vector";

	_size--;
}

template <typename T>
void MyVector<T>::insert(const T& data, unsigned idx)
{
	if (idx >= _size)
		throw std::out_of_range("Index out of range");

	if (_size == _capacity)
		resize(2 * _capacity);

	_size++;
	for (int i = _size - 1; i > idx; i--)
		_data[i] = std::move(_data[i - 1]);
	_data[idx] = data;
}

template <typename T>
void MyVector<T>::insert(T&& data, unsigned idx)
{
	if (idx >= _size)
		throw std::out_of_range("Index out of range");

	if (_size == _capacity)
		resize(2 * _capacity);

	_size++;
	for (int i = _size - 1; i > idx; i--)
		_data[i] = std::move(_data[i - 1]);
	_data[idx] = std::move(data);
}

template <typename T>
void MyVector<T>::erase(unsigned idx)
{
	if (idx >= _size)
		throw std::out_of_range("Index out of range");

	for (size_t i = idx; i < _size - 1; i++)
		_data[i] = std::move(_data[i + 1]);
	_size--;
	if (_size == _capacity / 4)
		resize(_capacity / 2);
}

template <typename T>
void MyVector<T>::clear()
{
	delete[] _data;
	_size = 0;
	_capacity = DEFAULT_CAP;
	_data = new T[_capacity];
}

template <typename T>
bool MyVector<T>::empty() const
{
	return _size == 0;
}

template <typename T>
T& MyVector<T>::operator[](const size_t idx)
{
	if (idx >= _size)
		throw std::out_of_range("Index out of range");
	return _data[idx];
}

template <typename T>
const T& MyVector<T>::operator[](const size_t idx) const
{
	if (idx >= _size)
		throw std::out_of_range("Index out of range");
	return _data[idx];
}