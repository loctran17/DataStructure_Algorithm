#include "stdafx.h"
#include "Prim_Graph.h"
#include <queue>
#include <set>
#include <iostream>


Prim_Graph::Prim_Graph()
{
}


Prim_Graph::~Prim_Graph()
{
	for (auto &item : allVertices)
		delete item;
}

void Prim_Graph::addEdge(const std::string &sourceName, const std::string &destName, int cost)
{
	Prim_Vertex* vsource = getVertex(sourceName);
	Prim_Vertex* vdest = getVertex(destName);
	vsource->adj.push_back(vdest);
	vdest->adj.push_back(vsource);
	for (auto &item : {vsource, vdest})
		item->adjCost.push_back(cost);
}

void Prim_Graph::printPath(const std::string& destName) const
{
	vpmap::const_iterator itr = vertexMap.find(destName);
	if (itr == vertexMap.end())
	{
		std::cout << "Destination is not found" << std::endl;
		return;
	}
	if (itr->second->path == nullptr)
	{
		std::cout << "Destination is not reachable" << std::endl;
		return;
	}
	printPath(*(itr->second));
	std::cout << std::endl;
}

void Prim_Graph::prim(const std::string &sourceName)
{
	Prim_Vertex* v = getVertex(sourceName);
	auto vertexCompare = [](Prim_Vertex *const &lhs, const Prim_Vertex *const &rhs) -> bool {
		return lhs->dist > rhs->dist; 
	};
	std::priority_queue <Prim_Vertex*, std::vector<Prim_Vertex*>, decltype(vertexCompare)> qv(vertexCompare);
	v->dist = 0;
	qv.push(v);
	v->inserted = true;
	

 	while (!qv.empty())
	{
		v = qv.top();
		qv.pop();
		v->known = true;
		//std::cout << v->name << " is selected " << std::endl;
		
		for (int i = 0; i < v->adj.size(); i++)
		{
			Prim_Vertex *w = v->adj[i];
			if (w->dist > v->adjCost[i] && w->known == false)
			{
				w->dist = v->adjCost[i];
				w->path = v;
				//std::cout << w->name << " updated " << ", dist = " << w->dist << std::endl;
				if (w->inserted == false)
				{
					qv.push(w);
					w->inserted = true;
				}
			}
		}
		//printAll();
	}
}

void Prim_Graph::printPath(const Prim_Vertex & v) const
{
	if (v.path != nullptr)
	{
		printPath(*(v.path));
		std::cout << "-->";
	}
	std::cout << v.name;
}

Prim_Vertex* Prim_Graph::getVertex(const std::string&name)
{
	auto found = vertexMap.find(name);
	if (found == vertexMap.end()) // not found
	{
		// create new vertex
		Prim_Vertex *v = new Prim_Vertex(name);
		allVertices.push_back(v);
		vertexMap.insert(vppair(name, v));
		return v;
	}
	else return found->second;
}

void Prim_Graph::printPrim()
{
	prim(allVertices[0]->name);
	for (auto item:allVertices)
	{
		if (item->path != nullptr)
		{
			std::cout << "(" << item->name << "," << item->path->name << ") ";
		}
	}
	std::cout << std::endl;
}

void Prim_Graph::printAll()
{
	for (auto item : allVertices)
	{
		if (item->path)
			std::cout << item->name << ", " << (item->path->name)  << ", " << item->dist << ", " << item->known << std::endl;
		else
			std::cout << item->name << ", 0 " << ", " << item->dist << ", " << item->known << std::endl;
	}
}

void Prim_Graph::clearAll()
{
	for (auto &item : allVertices)
		item->reset();
}