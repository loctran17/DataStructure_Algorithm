#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class User
{
private:
	int m_id;
	string m_name;
public:
	User(const int &id, const string &name) : m_id(id), m_name(name)
	{

	}
	const string& getName() const
	{
		return m_name;
	}
	const int& getID() const
	{
		return m_id;
	}
	bool operator<(const User& lhs) const
	{
		return  m_id < lhs.m_id;
	}
};

void map_stl_example_1()
{
	map<User, int> m_UserInfoMap = {
				pair<User,int>(User(1, "X"), 100),
				pair<User,int>(User(2, "Y"), 200),
				pair<User,int>(User(3, "Z"), 300) };

	for_each(m_UserInfoMap.begin(), m_UserInfoMap.end(),
		[](pair<User, int> elem)
		{
		cout << elem.first.getName() << ": " << elem.second << endl;
		});
}

class UserNameComparator
{
public:
	bool operator()(const User &lhs, const User &rhs) const
	{
		return lhs.getName() < rhs.getName();
	}
};

void map_stl_example_2()
{
	map<User, int, UserNameComparator> m_UserInfoMap = {
		pair<User,int>(User(1, "X"), 100),
		pair<User,int>(User(2, "Y"), 200),
		pair<User,int>(User(3, "Z"), 300) };

	for_each(m_UserInfoMap.begin(), m_UserInfoMap.end(),
		[](pair<User, int> elem)
	{
		cout << elem.first.getName() << ": " << elem.second << endl;
	});
}