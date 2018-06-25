#pragma once
#include <algorithm>

template <typename Object>
class Singly_Linked_List
{
private:
	struct Node
	{
		Object data;
		Node *next;
		Node(const Object& d = Object{}, Node *n = nullptr) : data(d), next(n) {}
		Node(Object && d, Node *n = nullptr) : std::move(d), next(n) {}
	};

public:
	// iterator
	class const_iterator
	{
	public:
		const_iterator() : current(nullptr) {}
		const Object& operator*() const
		{
			return retrieve();
		}
		const_iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		const_iterator& operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const const_iterator &rhs)
		{
			return current = rhs.current;
		}
		bool operator!=(const const_iterator &rhs)
		{
			return !(*this == rhs);
		}
	protected:
		Node* current;
		Object& retrieve() {
			return current->data;
		}
		const_iterator(Node *p) : current(p) {}
		friend Singly_Linked_List<Object>;
	};

	class iterator : public const_iterator
	{
	public:
		iterator() {}
		
		Object& operator*()
		{
			return const_iterator::retrieve();
		}
		const Object& operator*() const
		{
			return const_iterator::operator*();
		}
		iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		iterator& operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
	protected:
		iterator(Node *p) : const_iterator{ p }
		{}
		friend class Singly_Linked_List<Object>;
	};

	Singly_Linked_List()
	{
		init();
	}
	Singly_Linked_List(const Singly_Linked_List &rhs)
	{
		init();
		for (auto &x : rhs)
			push_back(x);
	}
	Singly_Linked_List(Singly_Linked_List &&rhs): theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}
	~Singly_Linked_List() 
	{
		theSize = 0;
		delete head;
		delete tail;
	}

	Singly_Linked_List& operator=(Singly_Linked_List &&rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		return *this;
	}
	Singly_Linked_List& operator=(const Singly_Linked_List &rhs)
	{
		Singly_Linked_List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/* access */
	iterator begin()
	{
		return head->next;
	}
	const_iterator begin() const
	{
		return head->next;
	}
	iterator end()
	{
		return tail;
	}
	const_iterator end() const
	{
		return tail;
	}
	int size() const
	{
		return theSize;
	}
	bool empty() const
	{
		return size() == 0;
	}
	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	Object& front()
	{
		return *begin();
	}
	const Object& front() const
	{
		return *begin();
	}
	
	/* push, pop */
	void push_front(const Object &x)
	{
		insert_after(head, x);
	}
	void push_front(Object &&x)
	{
		insert_after(head, x);
	}
	
	void pop_front()
	{
		erase_after(head);
	}
	
	/* iterator manipulation */

	/* insert x after itr */
	iterator insert_after(iterator itr, const Object &x)
	{
		Node *p = itr.current;
		theSize++;
		return (p->next = new Node(x, p->next));
	}
	iterator insert_after(iterator itr, Object &&x)
	{
		Node *p = itr.current;
		theSize++;
		return (p->next = new Node(std::move(x), p->next));
	}

	/* erase item after itr */
	iterator erase_after(iterator itr)
	{
		Node *p = itr.current, *pNext = p->next;
		iterator retVal{ p->next->next };
		p->next = p->next->next;
		delete pNext;
		theSize--;
		return retVal;
	}
	

// internal data
private:
	Node	*head;
	Node	*tail;
	int		theSize;

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
	}
};