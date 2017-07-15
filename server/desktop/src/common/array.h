#pragma once
#include "allocator.h"
#include <vector>
typedef long sizeT;
template <typename T>
class Array
{
	Allocator<T> *allocator;
public:
	Array();
	Array(size_t allocatedSize);
	Array(const Array& arr);
	Array(Array &&arr);
	~Array();
	void PushBack(const T& data);
	size_t Count() const;
	size_t Allocated() const;
	T* GetPointer();
	const T* GetPointer() const;
	const T& operator[] (size_t i) const;
	T& operator[] (size_t i);
	Array& operator = (const Array& arr);
	Array& operator = (Array &&arr);
	const T& AtIndex(size_t i) const;
	T& AtIndex(size_t i);
	void IndexOf();
	void Sort(IComporator<T> comparator = DefaultComparator);
};

template <typename T>
Array<T>::Array()
{
	allocator = new Allocator<T>();
	if (!allocator) ThrowException("Cnat alloc");
}

template <typename T>
Array<T>::Array(const Array<T>& other)
{
	allocator = NULL;
	*this = other;
}

template <typename T>
Array<T>::Array(Array &&arr)
{
	allocator = arr.allocator;
	arr.allocator = nullptr;
}

template <typename T>
Array<T>::Array(size_t sizeToAlloc)
{
	allocator = new Allocator<T>(sizeToAlloc);
	if (!allocator) ThrowException("Error alloc");
}

template <typename T>
Array<T>::~Array()
{
	delete allocator;
}

template <typename T>
void Array<T>::PushBack(const T& data)
{
	allocator->PushBack(data);
}

template <typename T>
T *Array<T>::GetPointer()
{
	return allocator->GetPointer();
}

template <typename T>
const T* Array<T>::GetPointer() const
{
	return allocator->GetPointer();
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& arr)
{
	if (!allocator)
		allocator = new Allocator<T>(*arr.allocator);
	else
		*allocator = *arr.allocator;
	return *this;
}

template <typename T>
Array<T>& Array<T>::operator = (Array &&arr)
{
	return *this;
}

template <typename T>
const T& Array<T>::operator[] (size_t i) const
{
	return allocator->AtIndex(i);
}

template <typename T>
const T& Array<T>::AtIndex(size_t i) const
{
	return allocator->AtIndex(i);
}


template <typename T>
T& Array<T>::operator[] (size_t i)
{
	return allocator->AtIndex(i);
}

template <typename T>
T& Array<T>::AtIndex(size_t i)
{
	return allocator->AtIndex(i);
}

template <typename T>
sizeT Array<T>::Count() const
{
	return allocator->Count();
}


template <typename T>
sizeT Array<T>::Allocated() const
{
	return allocator->Allocated();
}