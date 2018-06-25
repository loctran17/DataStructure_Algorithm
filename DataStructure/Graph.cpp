#include "stdafx.h"
#include "Graph.h"

using namespace std;

Graph::Graph()
{
}


Graph::~Graph()
{
	for (int i = 0; i < allVertices.size(); i++)
		delete allVertices[i];
}

void Graph::addEdge(const std::string &sourceName, const std::string &destName)
{
	Vertex* v = getVertex(sourceName);
	Vertex* w = getVertex(destName);
	v->adj.push_back(w);
}

void Graph::printPath(const string &destName) const
{
	vmap::const_iterator itr = vertexMap.find(destName);
	if (itr == vertexMap.end())
	{
		cout << "Destination vertex not found" << endl;
		return;
	}
	if (itr->second->dist == INT_MAX)
		cout << destName.c_str() << "is unreachable";
	else
		printPath(*(itr->second));
	cout << endl;
}
void Graph::unweighted(const std::string &startName)
{
	vmap::iterator itr = vertexMap.find(startName);
	if (itr == vertexMap.end())
	{
		cout << startName.c_str() << " is not a vertex in this graph" << endl;
		return;
	}
	clearAll(); // init configuration of table in unweighted shortest-path computation

	// except the original vertex
	queue<Vertex* > q;
	q.push(itr->second);
	itr->second->dist = 0;

	while (!q.empty())
	{
		Vertex *v = q.front(); q.pop();
		for (int i = 0; i < v->adj.size(); i++)
		{
			Vertex *w = v->adj[i];
			if (w->dist == INT_MAX)
			{
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}

// if vertexName is not present, add it to vertexMap
// In either case, return Vertex
Vertex * Graph::getVertex(const std::string &vertexName)
{
	vmap::iterator found = vertexMap.find(vertexName);
	if (found == vertexMap.end())
	{
		Vertex *vnew = new Vertex(vertexName);
		allVertices.push_back(vnew);
		vertexMap.insert(make_pair(vertexName, vnew));
		return vnew;
	}
	return found->second;
}

void Graph::printPath(const Vertex &dest) const
{
	if (dest.path != nullptr)
	{
		printPath(*dest.path);
		cout << " --> ";
	}
	cout << dest.name.c_str();
}

void Graph::clearAll()
{
	for (int i = 0; i < allVertices.size(); i++)
		allVertices[i]->reset();
}
