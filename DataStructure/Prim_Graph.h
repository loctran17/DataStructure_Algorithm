#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <map>

struct Prim_Vertex
{
	std::string		name; // vertex name
	int				dist; // distance
	Prim_Vertex		*path; // next node
	std::vector<Prim_Vertex*> adj; // ajacent list
	std::vector<int>		  adjCost;
	bool            inserted;
	bool			known;

	Prim_Vertex(const std::string &n) : name(n), known(false), inserted(false)
	{
		reset();
	}
	void reset()
	{
		path = nullptr;
		dist = INT_MAX;
	}
};

typedef std::map<std::string, Prim_Vertex*> vpmap;
typedef std::pair<std::string, Prim_Vertex*> vppair;

class Prim_Graph
{
public:
	Prim_Graph();
	~Prim_Graph();

	void addEdge(const std::string &sourceName, const std::string &destName, int cost = 1);
	void printPath(const std::string& sourceName) const;
	void prim(const std::string &sourceName);
	void printPrim();
private:
	void printPath(const Prim_Vertex& v) const;
	Prim_Vertex* getVertex(const std::string&nodeName);
	void clearAll();
	void printAll();
	std::vector<Prim_Vertex*> allVertices;
	vpmap vertexMap;
};

