#pragma once

template <typename T, bool less = true>
class IComparator
{
public:
	virtual bool Compare();
};

template <typename T>
class ICollection
{
public:
	virtual void Add(const T&) = 0;
	virtual ~ICollection() {};
	virtual size_t Count() = 0;
	virtual void Clear() = 0;
	virtual void Remove(const T &item) = 0;
	virtual T& AtIndex(size_t index) = 0;
	virtual const T& AtIndex(size_t index) const  = 0;
	virtual const T& operator [](size_t index) const = 0;
	virtual T& operator [] (size_t size) = 0;
	virtual void RemoveFirst() = 0;
	virtual void RemoveLast() = 0;
	virtual void RemoveAt(size_t index)=0;
};

