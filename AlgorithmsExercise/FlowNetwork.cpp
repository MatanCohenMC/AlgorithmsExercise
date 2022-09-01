#include "FlowNetwork.h"

void FlowNetwork::BFS(Graph G, vertex s)
{
	vertex u;
	vector<int> d;
	list<neighbor> AdjList;
	queue<vertex> Q;

	d.resize(G.GetAmountOfVertices() + 1);

	for(int i = 1 ; i <= G.GetAmountOfVertices() ; i++)
	{
		d[i] = INFINITY;
	}

	Q.push(s);
	d[s] = 0;

	while(!Q.empty())
	{
		u = Q.front();
		Q.pop();

		AdjList = G.GetAdjList(u);
		for(auto v : AdjList)
		{
			if (d[v.first] == INFINITY)
			{
				d[v.first] = d[u] + 1;
				Q.push(v.first);
			}
		}
	}


	// in d[t] there is the length of the lightest way from s to t 
}


void FlowNetwork::Dijkstra(Graph G, int weight, vertex s)
{
	PriorityQueue Q;

	vector<int> d;
	d.resize(G.GetAmountOfVertices() + 1);
	vector<vertex> p;
	d.resize(G.GetAmountOfVertices() + 1);

	Init(G, &d, &p, s);

	Q.BuildPriorityQueue(G.GetAmountOfVertices(), d);

	while (!Q.IsEmpty())
	{
		// delete max
		// ...
	}

}

// Initiate the d and p vectors
void FlowNetwork::Init(Graph G, vector<int>* d, vector<vertex>* p, vertex s)
{
	for (int v = 1; v <= G.GetAmountOfVertices(); v++)
	{
		d->at(v) = INFINITY;
	}

	d->at(s) = 0;

	for (int v = 1; v <= G.GetAmountOfVertices(); v++)
	{
		p->at(v) = NULL;
	}
}