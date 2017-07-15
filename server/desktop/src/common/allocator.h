#pragma once
#include "exception.h" 
typedef long sizeT;
template <typename T>
#define MEMORY_STEP 2
typedef long sizeT;
template <typename T>
#define MEMORY_STEP 2
class Allocator
{
	T* ptr;
	size_t allocatedSize;
	size_t elementsInBuffer;
public:
	Allocator();
	Allocator(size_t allocatedSize);
	Allocator(const Allocator& arr);
	Allocator(Allocator &&allocator);
	~Allocator();
	const T& AtIndex(size_t i) const;
	T& AtIndex(size_t i);
	const T* GetPointer() const;
	T* GetPointer();
	void PushBack(const T& data);
	void Resize();
	size_t Count();
	size_t Allocated();
	Allocator& operator = (const Allocator&);
};


template <typename T>
Allocator<T>::Allocator()
{
	allocatedSize = 0;
	ptr = NULL;
	elementsInBuffer = 0;
}

template <typename T>
Allocator<T>::Allocator(const Allocator<T>& arr)
{
	ptr = NULL;
	*this = arr;
}

template <typename T>
Allocator<T>::Allocator(size_t sizeToAlloc)
{
	allocatedSize = sizeToAlloc;
	if (allocatedSize == 0)
	{
		ptr = NULL;
	}
	else
	{
		ptr = new T[allocatedSize];

		if (!ptr)
			ThrowException("cant allocate");
	}
	elementsInBuffer = 0;
}

template <typename T>
Allocator<T>::Allocator(Allocator<T> &&allocator)
{
	ptr = allocator.ptr;
	allocatedSize = allocator.allocatedSize;
	elementsInBuffer = allocator.elementsInBuffer;
	allocator.ptr = NULL;
}

template <typename T>
Allocator<T>::~Allocator()
{
	delete[] ptr;
}

template <typename T>
void Allocator<T>::PushBack(const T& data)
{
	if (elementsInBuffer == allocatedSize)
		Resize();
	ptr[elementsInBuffer++] = data;
}

template <typename T>
void Allocator<T>::Resize()
{
	if (allocatedSize == 0)
	{
		allocatedSize = 1;
		ptr = new T[allocatedSize];
		if (!ptr) ThrowException("err");
		return;
	}
	sizeT newSize = allocatedSize * MEMORY_STEP;
	T *oldPtr = ptr;
	T *newPtr = new T[newSize];
	if (!newPtr) ThrowException("Cant reallcate");
	for (int i = 0; i < allocatedSize; i++)
		newPtr[i] = oldPtr[i];
	delete[] oldPtr;
	ptr = newPtr;
	allocatedSize *= MEMORY_STEP;
}

template <typename T>
T *Allocator<T>::GetPointer()
{
	return ptr;
}

template <typename T>
const T* Allocator<T>::GetPointer() const
{
	return ptr;
}

template <typename T>
T& Allocator<T>::AtIndex(size_t i)
{
	return ptr[i];
}

template <typename T>
const T& Allocator<T>::AtIndex(size_t i) const
{
	return ptr[i];
}

template <typename T>
size_t Allocator<T>::Count()
{
	return elementsInBuffer;
}

template <typename T>
size_t Allocator<T>::Allocated() 
{ 
	return allocatedSize; 
}


template <typename T>
Allocator<T>& Allocator<T>::operator = (const Allocator<T>& arr)
{
	delete[] ptr;
	allocatedSize = arr.allocatedSize;
	elementsInBuffer = arr.elementsInBuffer;
	if (allocatedSize == 0)
	{
		ptr = NULL;
		return *this;
	}
	ptr = new T[allocatedSize];
	if (!ptr) ThrowException("Cant alloc");
	for (int i = 0; i < elementsInBuffer; i++)
		ptr[i] = arr.ptr[i];
	return *this;
}