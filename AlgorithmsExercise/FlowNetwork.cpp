#include "FlowNetwork.h"

FlowNetwork::FlowNetwork(Graph* G, vertex s, vertex t)
{
	m_Graph = *G;
	m_S = s;
	m_T = t;
	d.resize(m_Graph.GetAmountOfVertices() + 1);
	p.resize(m_Graph.GetAmountOfVertices() + 1);
}




int FlowNetwork::FFbyBFS()
{
	list<neighbor> AdjList;
	list<Edge> P;

	for (int i = 1 ; i <= m_Graph.GetAmountOfVertices() ; i++)
	{
		AdjList = m_Graph.GetAdjList(i);
		for (auto e : AdjList)
		{
			e.second.SetFlow(0);

			if (!hasNegEdge(e.second.GetSrc(), e.second.GetDest())) // if (u,v) doesn't have negative edge
			{
				m_Graph.AddEdge(e.second.GetDest(), e.second.GetSrc(), 0); // add (v,u)
			}
		}
	}

	Graph residualGraph = m_Graph;
	BFS(residualGraph, m_S);

	while(d[m_T] != INFINITY)
	{
		findPathInResidualGraph(&P, m_S, m_T);
		int CfP = findResidualCap(P);
		updatePathInGraph(P, CfP);







		BFS(residualGraph, m_S);
	}


}

int FlowNetwork::findResidualCap(list<Edge> P)
{
	int edgeCap, minCap;

	minCap = P.front().GetCap();

	for (auto edge : P)
	{
		edgeCap = edge.GetCap();
		if (edgeCap < minCap)
		{
			minCap = edgeCap;
		}
	}

	return minCap;
}

void FlowNetwork::findPathInResidualGraph(list<Edge>* P, vertex s, vertex t)
{
	vertex i, u = t;
	list<neighbor> AdjList;

	while (p[u] != NULL)
	{
		AdjList = m_Graph.GetAdjList(p[u]);

		for (auto i: AdjList)
		{
			if (i.second.GetDest() == u)
			{
				(*P).push_front(i.second);
			}
		}

		u = p[u];
	}
}


void FlowNetwork::BFS(Graph G, vertex s)
{
	vertex u;
	list<neighbor> AdjList;
	queue<vertex> Q;

	for(int i = 1 ; i <= G.GetAmountOfVertices() ; i++)
	{
		d[i] = INFINITY;
		p[i] = NULL;
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
				p[v.first] = u;
				Q.push(v.first);
			}
		}
	}
	// in d[t] there is the length of the lightest way from s to t 
}




//void FlowNetwork::BFS(Graph G, vertex s)
//{
//	vertex u;
//	vector<int> d;
//	list<neighbor> AdjList;
//	queue<vertex> Q;
//
//	d.resize(G.GetAmountOfVertices() + 1);
//
//	for (int i = 1; i <= G.GetAmountOfVertices(); i++)
//	{
//		d[i] = INFINITY;
//	}
//
//	Q.push(s);
//	d[s] = 0;
//
//	while (!Q.empty())
//	{
//		u = Q.front();
//		Q.pop();
//
//		AdjList = G.GetAdjList(u);
//		for (auto v : AdjList)
//		{
//			if (d[v.first] == INFINITY)
//			{
//				d[v.first] = d[u] + 1;
//				Q.push(v.first);
//			}
//		}
//	}
//
//
//	// in d[t] there is the length of the lightest way from s to t 
//}


void FlowNetwork::Dijkstra(Graph G, int weight, vertex s)
{
	PriorityQueue Q;

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