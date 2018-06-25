#pragma once
#include <algorithm>

template <typename Object>
class vector
{
public:
	/* What is keyword explicit --> does not allow implicit 
	copy construtor (Vector a = 1;  error in compiler )*/
	explicit vector(int initSize = 0) : theSize(initSize),
		theCapacity{ initSize + SPACE_CAPACITY } 
	{
		//std::cout << "using my own vector" << std::endl;
		objects = new Object[theCapacity];
	}
	explicit vector(int initSize, const Object &value) : theSize(initSize),
		theCapacity{ initSize + SPACE_CAPACITY }
	{
		objects = new Object[theCapacity];
		for (int i = 0; i < theCapacity; i++)
			objects[i] = value;
	}

	// copy constructor
	vector(const vector &rhs) : theSize(rhs.theSize),
		theCapacity(rhs.theCapacity), objects(nullptr)
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; k++) {
			objects[k] = rhs.objects[k];
		}
	}

	// assignment operator
	vector& operator=(const vector &rhs) 
	{
		vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~vector()
	{
		delete[]objects;
	}

	vector(vector && rhs) : theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	vector& operator=(vector &&rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;
		Object *newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; k++)
		{
			// this less expensize but also means objects[k]
			// is unspecific
			newArray[k] = std::move(objects[k]);
		}

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[]newArray;
	}

	Object& operator[](int index) 
	{
		return objects[index];
	}
	const Object& operator[](int index) const
	{
		return objects[index];
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}
	void push_back(const Object &x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	// push_back support rvalue, less expessive
	// but xvalue will be unspecific
	void push_back(Object&& x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		--theSize;
	}

	const Object& back() const
	{
		return objects[theSize - 1];
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	static const int SPACE_CAPACITY = 16;
private:
	int theSize;
	int theCapacity;
	Object *objects;
};