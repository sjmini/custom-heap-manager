#ifndef __RLIST_H__
#define __RLIST_H__

#include <iostream>
#include <list>

#include "classes.h"

template <typename T>
class RList
{
private:
	std::list<T> l;

public:
	RList() {}
	~RList() {}

	void push(T item)
	{
		l.push_back(item);
		((T)item)->incRef();
	};

	T pop()
	{
		T ret = l.front();
		((T)ret)->decRef();
		l.pop_front();
		return ret;
	};
};

#endif