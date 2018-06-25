#include "stdafx.h"
#include "Dijkstra_Graph.h"


Dijkstra_Graph::Dijkstra_Graph()
{
}


Dijkstra_Graph::~Dijkstra_Graph()
{
	for (int i = 0; i < allVertices.size(); i++)
		delete allVertices[i];
}

// undirected graph
void Dijkstra_Graph::addEdge(const std::string& sourceName, const std::string& destName, int cost)
{
	Dijkstra_Vertex* v = getVertex(sourceName);
	Dijkstra_Vertex* w = getVertex(destName);
	v->adj.push_back(w);
	w->adj.push_back(v);
	for ( auto &item: { w,v })
	{
		item->adjCosts.push_back(cost);
	}
}
void Dijkstra_Graph::printPath(const std::string& destName) const
{
	divmap::const_iterator itr = vertexMap.find(destName);
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
void Dijkstra_Graph::dijkstra(const std::string& sourceName) 
{
	divmap::iterator itr = vertexMap.find(sourceName);
	if (itr == vertexMap.end())
		return;

	auto vertexCompare = [](Dijkstra_Vertex *const &lhs, const Dijkstra_Vertex *const &rhs) -> bool {return lhs->dist > rhs->dist; };
	std::priority_queue <Dijkstra_Vertex*, std::vector<Dijkstra_Vertex*>, decltype(vertexCompare)> qv(vertexCompare);

	// distance of source is 0;
	itr->second->dist = 0;
	qv.push(itr->second);

	while (!qv.empty())
	{
		Dijkstra_Vertex *v = qv.top(); qv.pop();
		v->known = true;
		for (int i = 0; i < v->adj.size(); i++)
		{
			Dijkstra_Vertex *w = v->adj[i];
			if (!w->known)
			{
				int    cwv = v->adjCosts[i];
				if (w->dist > (v->dist + cwv))
				{
					w->dist = v->dist + cwv;
					w->path = v;
					qv.push(w);
				}
			}
		}
	}
		 
}
void Dijkstra_Graph::printPath(const Dijkstra_Vertex& v) const
{
	if (v.path != nullptr)
	{
		printPath(*(v.path));
		std::cout << " --> ";
	}
	std::cout << v.name;
}
Dijkstra_Vertex* Dijkstra_Graph::getVertex(const std::string&name)
{
	divmap::iterator found = vertexMap.find(name);
	if (found == vertexMap.end())
	{
		Dijkstra_Vertex *vnew = new Dijkstra_Vertex(name);
		allVertices.push_back(vnew);
		vertexMap.insert(divpair(name, vnew));
		return vnew;
	}
	else return found->second;
}
void Dijkstra_Graph::clearAll()
{
	for (int i = 0; i < allVertices.size(); i++)
		allVertices[i]->reset();
}
