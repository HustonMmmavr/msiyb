/*!
\file array.h "server\desktop\src\common\array.h"
\authors I}{TI@NDR }{YEV
\copyright © MSiYB 2017
\license GPL license
\version 1.0
\date 20 July 2017
*/

#pragma once
#include "allocator.h"

#ifdef DEBUG
#define ThrowArrayException(msg)											\
{																		\
	throw ArrayException(msg, __FILE__, __FUNCTION__, __LINE__);			\
}

#define ThrowArrayExceptionWithCode(msg, code)							\
{																		\
	throw ArrayException(msg, __FILE__, __FUNCTION__, __LINE__, code);	\
}
#else
#define ThrowArrayException(msg)											\
{																		\
	throw ArrayException(msg);											\
}																	
#define void ThrowArrayExceptionWithCode(msg, code)						\
{																		\
	throw ArrayException(msg, code);										\
}
#endif
#include <exception>

std::exception;

// We may be need to create ne
class ArrayException : public Exception
{
	ArrayException() {}
	ArrayException(const char* message, const char *file, const char *function, int line, long errCode)
	{
		sprintf(this->message, "In file %s function %s line %d error occured.\n Error message: %s\n Error code: %d\n", file, function, line, message, errCode);
		this->errCode = errCode;
	}

	ArrayException(const char* message, const char *file, const char *function, int line)
	{
		sprintf(this->message, "In file %s function %s line %d error occured.\n Error message: %s\n", file, function, line, message);
		this->errCode = -1;
	}

	const char* what() const
	{
		return message;
	}

	void operator = (const ArrayException &other)
	{
		if (this != &other)
		{
			strcpy(message, other.what());
			errCode = other.GetErrorCode();
		}
	}

	long GetErrorCode() const
	{
		return errCode;
	}

	void SetErrorCode(long errCode)
	{
		this->errCode = errCode;
	}
};

class ArrayIndexException :public ArrayException
{

};

template <typename T>
class Array
{
public:
	
	/* Initialize allocator object */
	Array();
	
	/* Initialize allocator object with given size 
	\param[in] sizeToAlloc Size needed to initialize allocator  
	*/
	Array(size_t sizeToAlloc);
	
	/* Copy constructor (copy data from given array to new)
	\param [in] other Array, which data will be copied to new array
	*/
	Array(const Array& other);
	
	/* Move constructor (move data from given array to new) 
	\param[in] other Array which data will be moved to new array
	*/
	Array(Array &&other);
	
	/* Deletes allocator */
	~Array();
	
	/* Push element to the end of array 
	\param[in] data Reference to data which will be added at the end of array
	*/
	void PushBack(const T& data);
	
	/* Returns count of elements storaged in array */
	size_t Count() const;
	
	/* Returns size of allocated buffer in memory */
	size_t Allocated() const;
	
	/* Returns C-style pointer to begin of array */
	T* GetPointer();

	/* Retuens C-style const pointer to begin of array */
	const T* GetPointer() const;

	/* Operator = which copy all data to this array
	\ param[in] other Array, which data will be copied to this array
	*/
	Array& operator = (const Array& other);

	/* operator = which move all data to this array
	\param [in] other Array, which data will be moved to this array
	*/
	Array& operator = (Array &&other);
	
	/* Returns const reference for element of array at given positi
	\param[in] index Position of element in array 
	*/
	const T& operator[] (size_t i) const;

	/* Returns reference for element of array at given position 
	\param[in] index Position of element in array
	*/
	T& operator[] (size_t index);
	
	/* Returns const referens for element of array at given position
	\param [in] index Position of element in array
	*/
	const T& AtIndex(size_t index) const;
	
	/* Retrurns reference for element of array at given position
	\param[in] index Position of element in arra
	*/
	T& AtIndex(size_t index);

	/* i forget what it need to do, but i have to remember */
	void IndexOf();
	
	/* Sorts array. Sorting depens on comparator.
	\param[in] comparator Rule to compare objects in array.
	If comparator not sended, function uses default compar.
	*/
	void Sort(IComporator<T> comparator = DefaultComparator);
private:
	Allocator<T> *allocator ///< Pointer to allocator object, where data is storaged
};

template <typename T>
Array<T>::Array()
{
	allocator = new Allocator<T>();
	if (!allocator) ThrowArrayException("Cant allocate allocator object");
}

template <typename T>
Array<T>::Array(const Array<T>& other)
{
	allocator = NULL;
	*this = other;		// there we use operator = 
}

template <typename T>
Array<T>::Array(Array &&other)
{
	allocator = arr.allocator;	// copy reference to allocator object
	other.allocator = nullptr;	// set reference to allocator object in old array to NULL
}

template <typename T>
Array<T>::Array(size_t sizeToAlloc)
{
	allocator = new Allocator<T>(sizeToAlloc);
	if (!allocator) ThrowArraException("Error alloc");
}

template <typename T>
Array<T>::~Array()
{
	delete allocator;
}

template <typename T>
void Array<T>::PushBack(const T& data)
{
	allocator->PushBack(data);	// Push data to the end of allocator
}

template <typename T>
T *Array<T>::GetPointer()
{
	return allocator->GetPointer();	// get pointer of allocator buffer
}

template <typename T>
const T* Array<T>::GetPointer() const
{
	return allocator->GetPointer(); // get pointer of allocator buffer
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& other)
{
	// if old array hasn't got allocator we need to delete existing 
	// and create new  allocator 
	if (!allocator)
	{
		delete allocator;
		allocator = new Allocator<T>(*other.allocator);
		if (!allocator) TrowArrayExceptio("Cant allocate allocator!");
	}
	else
		*allocator = *other.allocator; // There we call peregrugen operator = 
	return *this; // this - reference to self object. *this - object
}

template <typename T>
Array<T>& Array<T>::operator = (Array &&other)
{
	delete allocator;
	allocator = other.allocato;
	other.allocator = NULL;
	return *this;
}

template <typename T>
const T& Array<T>::operator[] (size_t index) const
{
	return allocator->AtIndex(index);
}

template <typename T>
const T& Array<T>::AtIndex(size_t index) const
{
	return allocator->AtIndex(index);
}


template <typename T>
T& Array<T>::operator[] (size_t index)
{
	return allocator->AtIndex(index);
}

template <typename T>
T& Array<T>::AtIndex(size_t index)
{
	return allocator->AtIndex(index);
}

template <typename T>
size_t  Array<T>::Count() const
{
	return allocator->Count();
}


template <typename T>
size_t Array<T>::Allocated() const
{
	return allocator->Allocated();
}