#pragma once

#include <vector>
#include <list>
#include <algorithm>

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101): currentSize(0), theLists(size)  // size should be prime number
	{
		
	}
	bool insert(const HashedObj &x) 
	{
		auto &whichList = theLists[myhash(x)];
		auto itr = find(whichList.begin(), whichList.end(), x);
		if (itr != whichList.end())
			return false;
		whichList.push_back(x);
		if (++currentSize > theLists.size())
			rehash();
		return true;
	}
	bool insert(HashedObj &&x)
	{
		auto &whichList = theLists[myhash(x)];
		auto itr = std::find(whichList.begin(), whichList.end(), x);
		if (itr != whichList.end())
			return false;
		whichList.push_back(std::move(x));
		if (++currentSize > theLists.size())
			rehash();
		return true;
	}
	bool remove(const HashedObj& x) 
	{
		auto &whichList = theLists[myhash(x)];
		auto itr = find(whichList.begin(), whichList.end(), x);
		if (itr == whichList.end())
			return false;
		whichList.erase(itr);
		--currentSize;
		return true;
	}

	bool contains(const HashedObj& x) const
	{
		auto& whichList = theLists[myhash(x)];
		return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
	}
	void makeEmpty()
	{
		for (auto &whichList : theLists)
		{
			whichList.clear();
		}
	}

private:
	std::vector<std::list<HashedObj>> theLists; // The array of List
	std::size_t currentSize;

	bool isPrime(int n)
	{
		if (n <= 1 || n % 2 == 0) return false;
		if (n == 2 || n == 3) return true;
		for (int i = 3; i < sqrt(n); i += 2)
		{
			if (n % i == 0) return false;
		}
		return true;
	}
	int nextPrime(int n)
	{
		if (n % 2 == 0) n++;
		for (; !isPrime(n); n += 2)
			;
		return n;
 	}
	void rehash()
	{
		std::vector<std::list<HashedObj>> oldLists = theLists;

		theLists.resize(nextPrime(theLists.size() * 2));
		for (auto &item : theLists)
		{
			item.clear();
		}

		// Copy table over
		currentSize = 0;
		for (auto &thisList : oldLists)
		{
			for (auto &x : thisList)
				insert(std::move(x));
		}
	}
	std::size_t myhash(const HashedObj &x) const
	{
		static std::hash<HashedObj> hf;
		return hf(x) % theLists.size();
	}
};