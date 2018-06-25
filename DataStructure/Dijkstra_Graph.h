#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>


struct Dijkstra_Vertex
{
	std::string				name;   // name of Dijkstra_Vertex
	Dijkstra_Vertex					*path;  // bookkeeping for trace actual path
	int						dist;	// current minimum distance from the source Dijkstra_Vertex
	std::vector<Dijkstra_Vertex*>	adj;	// ajacent list
	std::vector<int>		adjCosts;
	bool					known;
	Dijkstra_Vertex(const std::string& vname) : name(vname)
	{
		reset();
	}
	void reset()
	{
		path = nullptr;
		dist = INT_MAX;
		known = false;
	}
};

typedef std::map<std::string, Dijkstra_Vertex*> divmap;
typedef std::pair<std::string, Dijkstra_Vertex*> divpair;

class Dijkstra_Graph
{
public:
	Dijkstra_Graph();
	~Dijkstra_Graph();

	void addEdge(const std::string& sourceName, const std::string& destName, int cost = 1);
	void printPath(const std::string& destName) const;
	void dijkstra(const std::string& sourceName);

private:
	void printPath(const Dijkstra_Vertex& v) const;
	Dijkstra_Vertex* getVertex(const std::string&name);
	void clearAll();

	divmap	vertexMap;
	std::vector<Dijkstra_Vertex*> allVertices;
};

