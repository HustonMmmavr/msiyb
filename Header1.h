#pragma once
template <typename T>
class LinkedList : public IList<T>
{

	LinkedList()
	{
		_head = _tail = _size = NULL;
	}

	LinkedList(LinkedList<T> &other)
	{
		ListNode *prevNode = NULL;
		size_t size = other.Count();
		for (size_t i = 0; i < size; i++)
		{
			ListNode *node = new ListNode(other[i]);
			node->next
				prevNode = node;

		}
	}

	LinkedList(Collection<T> &collection)
	{

	}

	LinkedList(size_t size)
	{

	}
	void Add(const T&)
	{
		ListNode *node = new ListNode(item);
		if (!node) ThrowListException("Cant allocate node!");
		if (tail)
			_tail->next = node;
		else
			_head = _tail = node;
	}

	T AtIndex(size_t index)
	{
		ListNode *node = _head;
		for (size_t i = 0; i < index; i++)
			node = node->_next;
		return node->data;
	}

	T operator [](size_t index)
	{
		return AtIndex(index);
	}

	void Remove(const T& item)
	{

	}

	void RemoveLast()
	{

	}

	void RemoveAt()
	{
		if (index > _size) ThrowListIndexException("Index out of range");
		ListNode *node = _head;
		for (size_t i = 0; i < _index; i++)
			node = node->next;

		if (node->next)
			node->next->prev = node->prev;
		if (node->prev)
			node->prev->next = node->next;
		delete[] node;
	}
private:
	//Allcator<T> *
	struct ListNode
	{
		T _data;
		ListNode *_prev;
		ListNode *_next;
		ListNode() _prev(NULL), _next(NULL) {}
		ListNode(const T& data) _data(data), _prev(NULL), _next(NULL) {}
	};

	ListNode _head;
	ListNode _tail;
	size_t _size;
};
