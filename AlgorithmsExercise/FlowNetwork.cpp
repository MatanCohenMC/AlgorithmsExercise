#include "FlowNetwork.h"

// Creating a flow network
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
	P.clear();
	RP.clear();
	int amountOfVertices = m_Graph.GetAmountOfVertices();

	/*for (int i = 1 ; i <= amountOfVertices; i++)
	{
		AdjList = m_Graph.GetAdjList(i);
		for (auto e : AdjList)
		{
			e.second.SetFlow(0);
			e.second.GetNegEdge()->SetFlow(0);
		}
	}*/

	Graph residualGraph = m_Graph;
	BFS(residualGraph, m_S);

	printD();

	while(d[m_T] != numeric_limits<int>::max())
	{
		// findPathInGraph(residualGraph, RP, m_S, m_T);
		// findPathInGraph(m_Graph, &P, m_S, m_T);
		int CfP = findResidualCap(residualGraph, RP);
		updatePathInGraph(m_Graph, &P, CfP);
		updatePathInResidualGraph(m_Graph, residualGraph ,&P,&RP);
		maxFlow += CfP;


		printD();
		m_Graph.PrintGraph();
		residualGraph.PrintGraph();

		BFS(residualGraph, m_S);

	
	}

	return maxFlow;
}

void FlowNetwork::updatePathInResidualGraph(Graph G, Graph RG, list<Edge*>* P, list<Edge*>* RP)
{
	//list<Edge*>::iterator itrP;
	//list<Edge*>::iterator itrRP;
	//itrP = P->begin();
	//itrRP = RP->begin();

	//while (P->end() != itrP)
	//{
	//	(*itrRP)->SetCap((*itrP)->GetCap() - (*itrP)->GetFlow()); // Cf(u,v) = C(u,v) - f(u,v)

	//	((*itrRP)->GetNegEdge())->SetCap((*itrP)->GetNegEdge()->GetCap() - (*itrP)->GetNegEdge()->GetFlow()); // Cf(v,u) = C(v,u) - f(v,u)

	//	++itrP;
	//	++itrRP;
	//}


	vertex u = m_T;
	list<neighbor> AdjList;
	Edge* edgePtrInG, *edgePtrInRG;
	

	while (p[u] != NULL)
	{
		edgePtrInG = &G.GetEdgePtr(p[u], u);
		edgePtrInRG = &RG.GetEdgePtr(p[u], u);

		edgePtrInRG->SetCap(edgePtrInG->GetCap() - edgePtrInG->GetFlow()); // Cf(u,v) = C(u,v) - f(u,v)

		edgePtrInRG->GetNegEdge()->SetCap(edgePtrInG->GetNegEdge()->GetCap() - edgePtrInG->GetNegEdge()->GetFlow()); // Cf(v,u) = C(v,u) - f(v,u)

		u = p[u];
	}
}

void FlowNetwork::updatePathInGraph(Graph G, list<Edge*>* P, int CfP)
{
	int newFlow;
	vertex u = m_T;
	list<neighbor> AdjList;
	Edge* edgePtr;
	
	/*while (p[u] != NULL)
	{
		edgePtr = &G.GetEdgePtr(p[u], u);
		newFlow = edgePtr->GetFlow() + CfP;
		edgePtr->SetFlow(newFlow);
		edgePtr->GetNegEdge()->SetFlow(-newFlow);

		u = p[u];
	}*/



	while (p[u] != NULL)
	{
		list<neighbor>* AdjListggggggg = m_Graph.SetAdjList(p[u]);
		for (auto i : *AdjListggggggg)
		{
			if (i.first == u)
			{
				newFlow = i.second.GetFlow() + CfP;;
				i.second.SetFlow(newFlow);
				i.second.GetNegEdge()->SetFlow(-newFlow);
			}
		}
	u = p[u];
	}




	/*vertex u = m_T;
	list<neighbor> AdjList;
	Edge* edgePtr;
	edgePtr = &G.GetEdgePtr(p[u], u);
	u = p[u];

	while (p[u] != NULL)
	{
		edgePtr = &G.GetEdgePtr(p[u], u);


		u = p[u];
	}*/
}

int FlowNetwork::findResidualCap(Graph G, list<Edge*> P)
{
	int edgeCap, minCap;
	vertex u = m_T;
	list<neighbor> AdjList;
	Edge* edgePtr;
	edgePtr = &G.GetEdgePtr(p[u], u);
	minCap = edgePtr->GetCap();
	u = p[u];

	while (p[u] != NULL)
	{
		edgePtr = &G.GetEdgePtr(p[u], u);
		edgeCap = edgePtr->GetCap();

		if (edgeCap < minCap)
		{
			minCap = edgeCap;
		}

		u = p[u];
	}

	return minCap;





	/*int edgeCap, minCap;

	minCap = P.front()->GetCap();

	for (auto edge : P)
	{
		edgeCap = edge->GetCap();
		if (edgeCap < minCap)
		{
			minCap = edgeCap;
		}
	}

	return minCap;*/
}

void FlowNetwork::findPathInGraph(Graph G, list<Edge*> *P, vertex s, vertex t)
{
	vertex u = t;
	list<neighbor> AdjList;
	Edge* edgePtr;

	while (p[u] != NULL)
	{
		edgePtr = &G.GetEdgePtr(p[u], u);
		P->push_front(edgePtr);
		u = p[u];
	}


	//while (p[u] != NULL)
	//{
	//	AdjList = G.GetAdjList(p[u]);
	//	itr = AdjList.begin();

	//	while (AdjList.end() != itr)
	//	{
	//		if (itr->second.GetDest() == u)
	//		{
	//			P->push_front(G.GetEdgePtr(p[u], u));


	//			//Edge* e = (Edge*)malloc(sizeof(Edge));
	//			//e = &(itr->second);
	//			//P->push_front(e);
	//			////P->front() = &(itr->second);

	//			break;
	//		}

	//		itr++;
	//	}

	//	u = p[u];
	//}

			/*	vertex i, u = t;
				list<neighbor> AdjList;

				while (p[u] != NULL)
				{
					AdjList = G.GetAdjList(p[u]);

					for (auto i : AdjList)
					{
						if (i.second.GetDest() == u)
						{
							P->push_front(&(i.second));
						}
					}

					u = p[u];
				}*/

}


void FlowNetwork::BFS(Graph G, vertex s)
{
	vertex u;
	list<neighbor> AdjList;
	queue<vertex> Q;
	int amountOfVertices = G.GetAmountOfVertices();


	for(int i = 1 ; i <= amountOfVertices; i++)
	{
		d[i] = numeric_limits<int>::max(); // infinity
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
			if (v.second.GetCap() != 0)
			{
				if (d[v.first] == numeric_limits<int>::max()) // infinity
				{
					d[v.first] = d[u] + 1;
					p[v.first] = u;
					Q.push(v.first);
				}
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

void FlowNetwork::printD()
{
	cout << "d[]: ";
	for (auto u : d)
	{
		cout << u << " ";
	}
	cout << "\n";
}