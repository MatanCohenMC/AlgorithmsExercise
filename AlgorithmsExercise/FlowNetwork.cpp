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
	int maxFlow = 0;
	list<neighbor> AdjList;
	list<Edge*> RP, P;

	for (int i = 1 ; i <= m_Graph.GetAmountOfVertices() ; i++)
	{
		AdjList = m_Graph.GetAdjList(i);
		for (auto e : AdjList)
		{
			e.second.SetFlow(0);
			e.second.GetNegEdge()->SetFlow(0);
		}
	}

	Graph residualGraph = m_Graph;
	BFS(residualGraph, m_S);

	while(d[m_T] != INFINITY)
	{
		findPathInGraph(residualGraph, &RP, m_S, m_T);
		findPathInGraph(m_Graph, &P, m_S, m_T);
		int CfP = findResidualCap(RP);
		updatePathInGraph(&P, CfP);
		updatePathInResidualGraph(&P,&RP);
		maxFlow += CfP;

		BFS(residualGraph, m_S);
	}

	return maxFlow;
}

void FlowNetwork::updatePathInResidualGraph(list<Edge*>* P, list<Edge*>* RP)
{
	list<Edge*>::iterator itrP;
	list<Edge*>::iterator itrRP;
	itrP = P->begin();
	itrRP = RP->begin();

	while (P->end() != itrP)
	{
		(*itrRP)->SetCap((*itrP)->GetCap() - (*itrP)->GetFlow()); // Cf(u,v) = C(u,v) - f(u,v)

		((*itrRP)->GetNegEdge())->SetCap((*itrP)->GetNegEdge()->GetCap() - (*itrP)->GetNegEdge()->GetFlow()); // Cf(v,u) = C(v,u) - f(v,u)

		++itrP;
		++itrRP;
	}
}

void FlowNetwork::updatePathInGraph(list<Edge*>* P, int CfP)
{
	int newFlow;

	for (auto e : *P)
	{
		newFlow = e->GetFlow() + CfP;
		e->SetFlow(newFlow);
		e->GetNegEdge()->SetFlow(-newFlow);
	}
}

int FlowNetwork::findResidualCap(list<Edge*> P)
{
	int edgeCap, minCap;

	minCap = P.front()->GetCap();

	for (auto edge : P)
	{
		edgeCap = edge->GetCap();
		if (edgeCap < minCap)
		{
			minCap = edgeCap;
		}
	}

	return minCap;
}

void FlowNetwork::findPathInGraph(Graph G, list<Edge*>* P, vertex s, vertex t)
{
	vertex i, u = t;
	list<neighbor> AdjList;

	while (p[u] != NULL)
	{
		AdjList = G.GetAdjList(p[u]);

		for (auto i: AdjList)
		{
			if (i.second.GetDest() == u)
			{
				P->push_front(&(i.second));
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