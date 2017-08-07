#pragma once
#include "linkedlist.h"

template <typename T>
class Stack
{
	Stack();
	Stack(const Stack &other);
	Stack(Stack &&other);
	Stack(const ICollection &collection);

	T& Top();
	T& Pop();
	
	const T& Top() const; 
	const T& Back();

};

template <typename T>
class Queue
{
public:
	Queue();
	Queue(const Queue& other);
	Queue(Queue &&other);
	Queue(const ICollection<T> & collection);
	
	T& Top();
	T& Back();
	
	const T& Top() const;
	const T& Back() const;
	
	bool IsEmpty() const;
	size_t Count() const;

	void Clear();

	void Push(const T& item);
	T& Pop();

	T& AtIndex(size_t index);
	const T& AtIndex(size_t index) const;

	T& operator [] (size_t index);
	const T& operator(size_t index) const;

	Queue operator = (const Queue &other);
	Queue operator = (Queue &&other);

private:
	ICollection<T> *_q;
};

template<typename T>
inline Queue<T>::Queue()
{
	_q = new LinkedList<T>();
}

template<typename T>
inline Queue<T>::Queue(const Queue & other)
{
	*_q = *(other._q);
}

template<typename T>
inline Queue<T>::Queue(Queue && other)
{
	_q = other._q;
	other._q = NULL;
}

template<typename T>
inline Queue<T>::Queue(const ICollection<T>& other)
{
	for (int i = 0; i < other.Count(); i++)
	{
		Push(other.AtIndex(i));
	}
}

template<typename T>
inline T& Queue<T>::Top()
{
	return _q.AtIndex(0);
}

template<typename T>
inline T& Queue<T>::Back()
{
	return _q.AtIndex(_q.Count()-1);
}

template<typename T>
inline const T& Queue<T>::Top() const
{
	return _q.AtIndex(0);
}

template<typename T>
inline const T& Queue<T>::Back() const
{
	return _q.AtIndex(_q.Count() - 1);
}

template<typename T>
inline bool Queue<T>::IsEmpty() const
{
	return _q.Count() == 0;
}

template<typename T>
inline size_t Queue<T>::Count() const
{
	return _q.Count();
}

template<typename T>
inline void Queue<T>::Clear()
{
	_q.Clear();
}

template<typename T>
inline void Queue<T>::Push(const T& item)
{
	_q.Add(item);
}

template<typename T>
inline T& Queue<T>::Pop()
{
	T item = _q.AtIndex(_q.Count() - 1);
	_q.RemoveAt(_q.Count() - 1);
	return item;
}

template<typename T>
inline T & Queue<T>::AtIndex(size_t index)
{
	return _q.AtIndex(index);
}

template<typename T>
inline const T & Queue<T>::AtIndex(size_t index) const
{
	return _q.AtIndex(index);
}

template<typename T>
inline T & Queue<T>::operator[](size_t index)
{
	_q.AtIndex(index);
}

template<typename T>
inline Queue Queue<T>::operator=(const Queue & other)
{
	_q.Clear();
	size_t size = other.Count();
	for (size_t  i = 0; i < size; i++)
	{
		_q.Add(other.AtIndex(i));
	}
	return *thi;
}

template<typename T>
inline Queue Queue<T>::operator=(Queue &&)
{
	delete _q;
	_q = other._q;
	other._q = NULL;
	return *this;
}

