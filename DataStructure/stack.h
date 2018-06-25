#pragma once
#include "singly_linked_list.h"

template <typename Object>
class stack
{
public:
	void push(const Object &x)
	{
		sll.push_front(x);
	}
	void push(Object &&x)
	{
		sll.push_front(x);
	}
	void pop()
	{
		sll.pop_front();
	}
	bool empty()
	{
		return sll.empty();
	}
	Object& top()
	{
		return sll.front();
	}
	const Object& top() const
	{
		return sll.front();
	}
	int size()
	{
		return sll.size();
	}
private:
	Singly_Linked_List<Object> sll;
};