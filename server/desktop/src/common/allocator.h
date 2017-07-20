#pragma once
/*!
\file locker.h "server\desktop\src\common\allocator.h"
\authors I}{TI@NDR }{YEV
\copyright © MSiYB 2017
\license GPL license
\version 1.0
\date 20 July 2017
*/

#include "../tools/exceptions/allocatorexception.h"

template <typename T>
class Allocator
{
public:
	
	/* Initializes buffer to null and counters to 0 */
	Allocator();
	
	/* Initialize buffer with given size
	\param[in] sizToAlloc Size needed to allocate 
	*/
	Allocator(size_t sizeToAlloc);
	
	/* Copy constructor (copy data from given allocator to new)
	\param[in] other Allocator which data will be copied to new object 
	*/
	Allocator(const Allocator& other);
	
	/* Move constructor (move data from given allocator to new)
	\param[in] other Allocator which data will be moved to new object
	*/
	Allocator(Allocator &&other);

	/* Deletes all data storaged in object */
	~Allocator();

	/* Returns const reference of element storeged at given position
	\param[in] index Position of element in buffe
	*/
	const T& AtIndex(size_t index) const;
	
	/* Returns const reference of element storeged in buffer at given position
	\param[in] index 
	*/
	T& AtIndex(size_t index);
	
	/* Returns const pointer to btion
*/
	const T* GetPointer() const;
	
	/* Returns t pointer to buffe *
	T* GetPointer();
	
	/* Returns const reference of element storeged at given position
	\param[in] ind
	*/
	void PushBack(const T &data);
	
	/* Returns const reference of element storeged at given position
	\param[in] ind
	*/
	void Resize();
	
	/* Returns const reference of element storeged at given position
	\param[in] ind
	*/
	size_t Count();
	
	
	size_t Allocated();


	Allocator& operator = (const Allocator &other);
private:
	T* pBuffer;						///< Pointer to linea buffer 
	size_t allocatedSize;			///< Size of allocated buffer
	size_t elementsInBuffer;		///< Count of elements storaged in buffer
};


template <typename T>
Allocator<T>::Allocator()
{
	allocatedSize = 0;
	pBuffer = NULL;
	elementsInBuffer = 0;
}

template <typename T>
Allocator<T>::Allocator(const Allocator<T>& arr)
{
	pBuffer = NULL;	// Set b=pointer to buffer to NULL, because of correc delet in operator =
	*this = arr;	// operator = is peregruge
}

template <typename T>
Allocator<T>::Allocator(size_t sizeToAlloc)
{
	allocatedSize = sizeToAlloc;
	if (allocatedSize == 0)
	{
		pBuffer = NULL;
	}
	else
	{
		pBuffer = new T[allocatedSize];
		if (!pBuffer)
			ThrowAllocatorException("Cant allocate buf");
	}
	elementsInBuffer = 0;
}

template <typename T>
Allocator<T>::Allocator(Allocator<T> &&allocator)
{
	pBuffer = allocator.pBuffer;
	allocatedSize = allocator.allocatedSize;
	elementsInBuffer = allocator.elementsInBuffer;
	allocator.pBuffer = NULL;
}

template <typename T>
Allocator<T>::~Allocator()
{
	delete[] pBuffer;
}

template <typename T>
void Allocator<T>::PushBack(const T& data)
{
	if (elementsInBuffer == allocatedSize)
		Resize();
	pBuffer[elementsInBuffer++] = data;
}

template <typename T>
void Allocator<T>::Resize()
{
	if (allocatedSize == 0)
	{
		allocatedSize = 1;
		pBuffer = new T[allocatedSize];
		if (!pBuffer) ThrowException("err");
		return;
	}
	sizeT newSize = allocatedSize * MEMORY_STEP;
	T *oldpBuffer = pBuffer;
	T *newpBuffer = new T[newSize];
	if (!newpBuffer) ThrowException("Cant reallcate");
	for (int i = 0; i < allocatedSize; i++)
		newpBuffer[i] = oldpBuffer[i];
	delete[] oldpBuffer;
	pBuffer = newpBuffer;
	allocatedSize *= MEMORY_STEP;
}

template <typename T>
T *Allocator<T>::GetPointer()
{
	return pBuffer;
}

template <typename T>
const T* Allocator<T>::GetPointer() const
{
	return pBuffer;
}

template <typename T>
T& Allocator<T>::AtIndex(size_t index)
{
	return pBuffer[index];
}

template <typename T>
const T& Allocator<T>::AtIndex(size_t index) const
{
	return pBuffer[i];
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
	delete[] pBuffer;	// we need to delete old data 
	allocatedSize = arr.allocatedSize;
	elementsInBuffer = arr.elementsInBuffer;
	
	// if given allocator was empty we need to check it, else will be error in new T[0]
	if (allocatedSize == 0)
	{
		pBuffer = NULL;
		return *this;
	}

	pBuffer = new T[allocatedSize];
	if (!pBuffer) ThrowException("Cant alloc");

	// Copy all given data (we cant use memcpy if elements is objects)
	for (int i = 0; i < elementsInBuffer; i++)
		pBuffer[i] = arr.pBuffer[i];

	return *this;
}