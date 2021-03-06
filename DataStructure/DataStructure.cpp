// DataStructure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "BinarySearchTree.h"
#include "AVL_Tree.h"
#include "HashTable.h"
#include "Graph.h"
#include "Dijkstra_Graph.h"
#include "Prim_Graph.h"

#include <iostream>

// application with myself vector.
vector<int> get_all_primes(int n)
{
	vector<bool> check_primes(n+1, true); // 
	check_primes[0] = false;
	check_primes[1] = false;

	for (int i = 2; i < sqrt(n); i++)
	{
		if (check_primes[i]  == true)
		{
			for (int j = i * i; j < n; j += i)
			{
				check_primes[j] = false;
			}
		}
	}
	vector<int> result;

	for (int i = 0; i < n; i++)
	{
		if (check_primes[i] == true)
		{
			result.push_back(i);
		}
	}
	return result;
}


// LCS: dynamic programming
int lcs(const std::string &X, const std::string &Y)
{
	// 
	int n = X.size();
	int m = Y.size();

	std::vector<std::vector<int>> L(n + 1);
	for (int j = 0; j < L.size(); j++)
	{
		L[j] = std::vector<int>(m + 1);
	}

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;
			else
				L[i][j] = std::max<int>(L[i - 1][j], L[i][j - 1]);
		}
	}
	return L[n][m];
}


// -1 if not found, otherwise return the starting index
int pattern_matching(const std::string &T, const std::string &P)
{
	int n = T.size();
	int m = P.size();
	for (int i = 0; i < (n - m); i++)
	{
		int j = 0;
		while (j < m && T[i+j] == P[j]) j++;
		if (j >= m) return i;
	}
	return -1;
}

extern void map_stl_example_1();
extern void map_stl_example_2();
int main()
{
	vector<int> vi(2);
	vi[0] = 0; vi[1] = 1;
	vi.push_back(2);
	std::cout << "vector checking ..." << std::endl;
	for (auto item : vi) {
		std::cout << item << std::endl;
	}

	list<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	std::cout << "list checking ..." << std::endl;
	for (auto item : li) {
		std::cout << item << std::endl;
	}

	stack<int> si;
	si.push(4);
	si.push(5);
	si.push(6);
	std::cout << "stack checking ..." << std::endl;
	while (!si.empty())
	{
		std::cout << si.top() << std::endl;
		si.pop();
	}

	queue<int> qi;
	std::cout << "queue checking ..." << std::endl;
	qi.enqueue(1);
	qi.enqueue(2);
	qi.enqueue(3);
	qi.enqueue(4);
	while (!qi.empty())
	{
		std::cout << qi.dequeue() << std::endl;
	}

	BinarySearchTree<int> bst;
	std::cout << "BST checking ..." << std::endl;
	bst.insert(1);
	bst.insert(8);
	bst.insert(4);
	bst.insert(9);
	bst.insert(7);
	bst.printTree(std::cout);
	std::cout << std::endl;

	AVL_Tree<int> avlT;
	std::cout << "AVL Tree checking ..." << std::endl;
	avlT.insert(1);
	avlT.insert(8);
	avlT.insert(4);
	avlT.insert(9);
	avlT.insert(7);
	avlT.printTree(std::cout);
	std::cout << std::endl;

	std::cout << "checking prime number ... " << std::endl;
	vector<int> result = get_all_primes(1000);
	for (auto item : result)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;

	HashTable<int> ht;
	std::cout << "checking separate chaining hash table ... " << std::endl;
	ht.insert(1);
	ht.insert(2);
	ht.insert(3);

	std::cout << ht.contains(1) << std::endl;
	std::cout << ht.contains(2) << std::endl;
	std::cout << ht.contains(3) << std::endl;
	std::cout << ht.contains(4) << std::endl;

	ht.remove(2);

	std::cout << ht.contains(1) << std::endl;
	std::cout << ht.contains(2) << std::endl;
	std::cout << ht.contains(3) << std::endl;
	std::cout << ht.contains(4) << std::endl;


	Graph graph;
	std::cout << "checking unweighted shorted-path ... " << std::endl;
	graph.addEdge("v1", "v2");
	graph.addEdge("v1", "v3");
	graph.addEdge("v2", "v4");
	graph.addEdge("v2", "v5");
	graph.addEdge("v3", "v1");
	graph.addEdge("v3", "v6");
	graph.addEdge("v4", "v3");
	graph.addEdge("v4", "v5");
	graph.addEdge("v4", "v6");
	graph.addEdge("v4", "v7");
	graph.addEdge("v5", "v7");
	graph.addEdge("v7", "v6");
	graph.unweighted("v3");
	graph.printPath("v7");
	graph.printPath("v5");
	graph.printPath("v1");


	Dijkstra_Graph digraph;
	std::cout << "checking dijkstra shorted-path ... " << std::endl;
	digraph.addEdge("v1", "v2", 2);
	digraph.addEdge("v1", "v3", 4);
	digraph.addEdge("v1", "v4", 1);
	digraph.addEdge("v2", "v4", 3);
	digraph.addEdge("v2", "v5", 10);
	digraph.addEdge("v3", "v1", 4);
	digraph.addEdge("v3", "v6", 5);
	digraph.addEdge("v4", "v3", 2);
	digraph.addEdge("v4", "v5", 7);
	digraph.addEdge("v4", "v6", 8);
	digraph.addEdge("v4", "v7", 4);
	digraph.addEdge("v5", "v7", 6);
	digraph.addEdge("v7", "v6", 1);
	digraph.dijkstra("v3");
	digraph.printPath("v7");
	digraph.printPath("v5");
	digraph.printPath("v1");


	Prim_Graph pgraph;
	std::cout << "checking dijkstra shorted-path ... " << std::endl;
	pgraph.addEdge("v1", "v2", 2);
	pgraph.addEdge("v1", "v3", 4);
	pgraph.addEdge("v1", "v4", 1);
	pgraph.addEdge("v2", "v3", 3);
	pgraph.addEdge("v2", "v5", 10);
	pgraph.addEdge("v3", "v1", 4);
	pgraph.addEdge("v3", "v6", 5);
	pgraph.addEdge("v4", "v3", 2);
	pgraph.addEdge("v4", "v5", 7);
	pgraph.addEdge("v4", "v6", 8);
	pgraph.addEdge("v4", "v7", 4);
	pgraph.addEdge("v5", "v7", 6);
	pgraph.addEdge("v7", "v6", 1);
	pgraph.printPrim();

	std::cout << "checking lcs function ... " << std::endl;
	std::string X = "AGGTAB";
	std::string Y = "GXTXAYB";
	std::cout << lcs(X, Y) << std::endl;

	std::cout << pattern_matching("abacaabaccabacabaabb", "abacab") << std::endl;

	map_stl_example_1();
	map_stl_example_2();
	getchar();
    return 0;
}

