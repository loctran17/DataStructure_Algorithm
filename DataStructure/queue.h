#pragma once
#include <algorithm>

template <typename Object>
class queue
{

// Big-Five
public:
	// TODO
	queue(): theSize(0), front_pos(0), back_pos(-1)
	{
		
	}

	// TODO
	queue(const queue &rhs): theSize(rhs.theSize), front_pos(rhs.front_pos), back_pos(rhs.back_pos)
	{
		for (int i = 0; i < theSize; i++) 
		{
			theArray[i] = rhs.theArray[i];
		}
	}

	// TODO
	queue(queue && rhs): theSize(rhs.theSize), front_pos(rhs.front_pos), back_pos(rhs.back_pos)
	{
		for (int i = 0; i < theSize; i++)
		{
			theArray[i] = rhs.theArray[i];
		}
		rhs.theSize = 0;
		rhs.front_pos = 0;
		rhs.back_pos = -1;
	}

	// TODO
	queue& operator=(const queue& rhs)
	{
		theSize = rhs.theSize, front_pos = rhs.front_pos, back_pos = rhs.back_pos;
		for (int i = 0; i < theSize; i++)
		{
			theArray[i] = rhs.theArray[i];
		}
	}
	queue& operator=(queue &&rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(front_pos, rhs.front_pos);
		std::swap(back_pos, rhs.back_pos);
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	Object& front()
	{
		return theArray[front_pos];
	}
	const Object& front() const
	{
		return theArray[front_pos];
	}
	Object& back()
	{
		return theArray[back_pos];
	}
	const Object& back() const
	{
		return theArray[back_pos];
	}
	bool empty()
	{
		return theSize == 0;
	}
	int size()
	{
		return theSize;
	}
	void enqueue(const Object &x)
	{
		// wrapped around to the beginning
		if (back_pos == capacity - 1)
			back_pos = -1;
		theArray[++back_pos] = x;
		//std::cout << "back = " << back_pos << endl;
		theSize++;
	}
	void enqueue(Object&& x)
	{
		// wrapped around to the beginning
		if (back_pos == capacity - 1)
			back_pos = -1;
		theArray[++back_pos] = std::move(x);
		theSize++;
		//std::cout << "move back = " << back_pos << ", size = " << theSize << std::endl;
	}
	Object& dequeue()
	{
		// wrapped around to the beginning
		if (front_pos == capacity - 1)
			front_pos = 0;
		theSize--;
		//std::cout << "front = " << front_pos << endl;
		return theArray[front_pos++];
	}
	int capicity()
	{
		return capacity;
	}

private:
	static const int SPACE_CAPACITY = 1024;
	int capacity = SPACE_CAPACITY;
	Object  theArray[SPACE_CAPACITY];
	int front_pos;
	int back_pos;
	int theSize;
};