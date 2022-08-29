#include "Graph.h"


void Graph::MakeEmptyGraph(int n)
{
	adjLists.resize(n);
	for (int i = 0; i < n; i++)
	{
		adjLists[i].clear();
	}
}

list<vertex> Graph::GetAdjList(int u)
{
	return adjLists[u];
}

void Graph::AddEdge(int u, int v, int c)
{
	Edge newEdge(u, v, c, 0);

	// add edge to graph
}
void Graph::RemoveEdge(int u, int v)
{
	
}