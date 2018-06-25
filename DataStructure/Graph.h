#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <limits.h>


struct Vertex
{
	std::string				name; // Vertex name
	std::vector<Vertex *>	adj; // Adjacent vertices
	int						dist; // cost
	Vertex					*path; // previous vertex on shortest path, bookkeeping

	Vertex(const std::string& vname) : name(vname)
	{
		reset();
	}
	void reset()
	{
		dist = INT_MAX;
		path = nullptr;
	}
};

typedef std::map<std::string, Vertex *> vmap;
typedef std::pair<std::string, Vertex*> vpair;

class Graph
{
public:
	Graph();
	~Graph();
	
	void addEdge(const std::string &sourceName, const std::string &destName);
	void printPath(const std::string &destName) const;
	void unweighted(const std::string &startName);

private:
	Vertex * getVertex(const std::string &vertexName);
	void printPath(const Vertex &dest) const;
	void clearAll();

	vmap vertexMap;
	std::vector<Vertex* > allVertices;
};

