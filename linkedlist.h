#pragma once

#define ThrowListException(msg) return;
#define ThrowListIndexException(msg) return;

/*!
\class LinkedList linkedlist.h "server\desktop\src\common\linkedlist.h"
\author Alexandr Barulev
\brief LinkedList implements node list
*/

template <typename T, bool less = false>
class IPredicate 
{
	virtual ~IPredicate() = 0;
	virtual void Compare(const T& item) = 0;
};

#include "icollection.h"
template <typename T>
class LinkedList : public ICollection<T>
{
public:
	LinkedList();
	LinkedList(const ICollection<T> &other);
	LinkedList(LinkedList<T> &&other);
	LinkedList(size_t size);
	~LinkedList();

	void Add(const T&);
	const T& AtIndex(size_t index) const;
	T& AtIndex(size_t index);
	const T& operator[](size_t index) const;
	T& operator [] (size_t index);
	void InsertAt(const T &item, size_t position);
	void RemoveFirst();
	void Remove(const T& item, const IPredicate<T, bool>& comparator);
	void RemoveAll(const T& data, const IPredicate<T, bool>& comparator);
	void RemoveLast();
	void RemoveAt(size_t index);
	void Clear();
	size_t Count();
	LinkedList operator = (const ICollection &other);
	LinkedList operator = (LinkedList &&other);
private:

	template <typename D>
	struct ListNode
	{
		D _data;
		ListNode *_prev;
		ListNode *_next;
		ListNode(): _prev(NULL), _next(NULL) {}
		ListNode(const T& data): _data(data), _prev(NULL), _next(NULL) {}
	};

	ListNode<T> *AtIndex(size_t index, int param);	
	ListNode<T> *_head;
	ListNode<T> *_tail;
	size_t _size;
};

template <typename T>
LinkedList<T>::ListNode<T> *LinkedList<T>::AtIndex(size_t index, int param)
{
	ListNode<T> *node = _head;
	for (size_t i = 0; i < index; i++)
		node = node->_next;
	return node;
}


template <typename T> 
LinkedList<T>::LinkedList()
{
	_head = _tail = NULL;
	_size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const ICollection<T> &other)
{
	if (other.Count() > 0)
	{
		ListNode *prevNode = new ListNode(other.AtIndex(0));
		if (!prevNode) ThrowListException("Cant Allocate node");
		size_t size = other.Count();

		_size = size;
		for (size_t i = 1; i < size; i++)
		{
			ListNode *newNode = new ListNode(other.AtIndex(i));
			if (!newNode) ThrowListException("Cant Allocate node");
			node->_prev = prevNode;
			prevNode->_next = newNode;
		}
	}
}


template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other)
{
	Clear();
	_tail = other._tail;
	_head = other._head;
	_size = other._size;
	other._head = NULL;
	other._tail = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(size_t size)
{
	ListNode<T> *prevNode = new ListNode<T>();
	if (!prevNode) ThrowListExcdeption("Cant Allocate nod");

	for (size_t i = 1; i < size; i++)
	{
		ListNode<T> *node = new ListNode<T>();
		node->prev = prevNode;
		prevNode->next = node;
	}
	_size = size;
}



template <typename T>
LinkedList<T>::LinkedList(const Array<T> &arr)
{
	if (arr.Count() > 0)
	{
		ListNode<T> *prevNode = new ListNode<T>(arr.AtIndex(0));
		if (!prevNode) ThrowListException("Cant Allocate node");
		size_t size = arr.Count();
		_size = size;

		for (size_t i = 1; i < size; i++)
		{
			ListNode<T> *newNode = new ListNode(arr.AtIndex(i));
			if (!newNode) ThrowListException("Cant Allocate node!");
			node->_prev = prevNode;
			prevNode->_next = newNode;
		}
	}
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}


template <typename T>
void LinkedList<T>::Add(const T& item)
{
	ListNode<T> *node = new ListNode<T>(item);
	if (!node) ThrowListException("Cant allocate node!");
	if (_tail)
	{
		_tail->_next = node;
		node->_prev = _tail;
		_tail = node;
	}
	else
		_head = _tail = node;
	_size += 1;
}

template <typename T>
T& LinkedList<T>::AtIndex(size_t index)
{
	ListNode<T> *node = AtIndex(index, 1);
	return node->_data;
}

template <typename T>
void LinkedList<T>::Clear()
{
	ListNode<T> *node = _head;
	for (int i = 0; i < _size; i++)
	{
		ListNode<T> *nextNode = node->_next;
		delete node;
		node = nextNode;
	}
}

template <typename T>
T& LinkedList<T>::operator [](size_t index)
{
	return AtIndex(index);
}

template <typename T> 
const T& LinkedList<T>::AtIndex(size_t index) const
{
	ListNode<T> *node = (const_cast<LinkedList<T>* >(this))->AtIndex(index, 1);
	return node->_data;
}

template <typename T>
const T& LinkedList<T>::operator [] (size_t index) const
{
	return AtIndex(index);
}

template <typename T>
LinkedList<T> LinkedList<T>::operator = (const ICollection<T> &other)
{
	size_t size = other.Count();
	if (size > 0)
	{
		ListNode<T> *prevNode = new ListNode<T>(other.AtIndex(0));

		for (size_t i = 1; i < size; i++)
		{
			ListNode<T> *node = new ListNode<T>(other.AtIndex(i));
			node->_prev = prevNode;
			prevNode->_next = node;
			prevNode = node;
		}
	}
	_size = size;
	return *this;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator = (LinkedList<T> &&other)
{
	Clear();
	_head = other._head;
	_tail = other._tail;
	_size = other._size;
	other._size = 0;
	other._head = NULL;
	other._tail = NULL;
	return *this;
}

template<typename T>
void LinkedList<T>::InsertAt(const T & item, size_t position)
{
	if (position <= _size)
	{
		ListNode *node = new ListNode(item);
		if (!node) ThrowListException("Cant Allocate node");

		if (position == _size)
			Add(item);

		if (position == 0)
		{
			node->_next = _head;
			_head = node;
		}

		ListNode<T> *newPrev = AtIndex(position - 1);
		ListNode<T> *newNext = newPrev->_next;
		
		node->_prev = newPrev;
		newPrev->_next = node;
		
		node->_next = newNext;
		newNext->_prev = node;
		_size += 1;
	}
	else
		ThrowListIndexExeption("Index out of range");
}

template<typename T>
inline void LinkedList<T>::RemoveFirst()
{
	if (Count() == 0)
	{
		ThrowListIndexException();
	}
	ListNode<T> *newHead = _head->_next;
	delete _head;
	_head = newHead;
}

template <typename T>
void LinkedList<T>::RemoveAt(size_t index)
{
	if (index > _size) ThrowListIndexException("Index out of range");
	ListNode<T> *node = _head;
	for (size_t i = 0; i < index; i++)
		node = node->_next;

	if (node->_next)
		node->_next->_prev = node->_prev;
	if (node->_prev)
		node->_prev->_next = node->_next;
	_size--;
	delete node;
}

template<typename T>
inline size_t LinkedList<T>::Count()
{
	return _size;
}

template <typename T>
void LinkedList<T>::Remove(const T& item, const IPredicate<T, bool>& comparator)
{
	for (size_t i = 0; i < _size; i++)
	{
		if (comparator.Compare(item))
		{
			RemoveAt(i);
		}
	}
}

template<typename T>
inline void LinkedList<T>::RemoveAll(const T& data, const IPredicate<T, bool>& comparator)
{
}

template <typename T>
void LinkedList<T>::RemoveLast()
{
	if (_size < 0)
	{
		ListNode<T> * node = _tail->_prev;
		delete _tail;
	}
	else
		ThrowListException("List is empty");

	ListNode<T> * node = _tail;
	_size--;
}