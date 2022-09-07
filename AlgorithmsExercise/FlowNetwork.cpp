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




int FlowNetwork::FFbyBFS(vector<vertex> *S, vector<vertex> *T)
{
	int maxFlow = 0;
	//int max = numeric_limits<int>::max();
	int max = INT8_MAX;
	list<neighbor> AdjList;
	list<Edge*> RP, P;
	P.clear();
	RP.clear();
	int amountOfVertices = m_Graph.GetAmountOfVertices();
	Graph residualGraph = m_Graph;
	BFS(residualGraph, m_S);

	//printD();

	while(d[m_T] != max)
	{
		int CfP = findResidualCap(residualGraph, RP);
		updatePathInGraph(m_Graph, &P, CfP);
		updatePathInResidualGraph(&m_Graph, &residualGraph ,&P,&RP);
		maxFlow += CfP;
		
		/*m_Graph.PrintGraph();
		cout << "/////////////////////////////////////// \n";
		residualGraph.PrintGraph();*/

		BFS(residualGraph, m_S);
		//printD();
	
	}

	BFS(residualGraph, m_S);
	S->clear(); T->clear();
	for (int i=1; i <= amountOfVertices ; i++)
	{
		if (d[i] != max)
		{
			S->push_back(i);
		}
		else
		{
			T->push_back(i);
		}
	}
	
	return maxFlow;
}

int FlowNetwork::FFbyDijkstra(vertex s, vertex t, vector<vertex>* S, vector<vertex>* T)
{
	m_S = s;
	m_T = t;
	int maxFlow = 0;
	int max = INT8_MAX;
	list<neighbor> AdjList;
	list<Edge*> RP, P;
	P.clear();
	RP.clear();
	int amountOfVertices = m_Graph.GetAmountOfVertices();
	Graph residualGraph = m_Graph;

	Dijkstra(residualGraph, m_S);

	//printD();

	while (d[m_T] != -1 && d[m_T] != 0)
	{
		int CfP = findResidualCap(residualGraph, RP);
		updatePathInGraph(m_Graph, &P, CfP);
		updatePathInResidualGraph(&m_Graph, &residualGraph, &P, &RP);
		maxFlow += CfP;

		//m_Graph.PrintGraph();
		//cout << "/////////////////////////////////////// \n";
		//residualGraph.PrintGraph();

		Dijkstra(residualGraph, m_S);
		//printD();

	}

	BFS(residualGraph, m_S);
	S->clear(); T->clear();
	for (int i = 1; i <= amountOfVertices; i++)
	{
		if (d[i] != max)
		{
			S->push_back(i);
		}
		else
		{
			T->push_back(i);
		}
	}

	return maxFlow;
}

void FlowNetwork::updatePathInResidualGraph(Graph* G, Graph* RG, list<Edge*>* P, list<Edge*>* RP)
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

	/////////////////////////////////////////////////// best one yet
	//vertex u = m_T;
	//list<neighbor> AdjList;
	//Edge* edgePtrInG, *edgePtrInRG;
	//

	//while (p[u] != NULL)
	//{
	//	edgePtrInG = &G.GetEdgePtr(p[u], u);
	//	edgePtrInRG = &RG.GetEdgePtr(p[u], u);

	//	edgePtrInRG->SetCap(edgePtrInG->GetCap() - edgePtrInG->GetFlow()); // Cf(u,v) = C(u,v) - f(u,v)

	//	edgePtrInRG->GetNegEdge()->SetCap(edgePtrInG->GetNegEdge()->GetCap() - edgePtrInG->GetNegEdge()->GetFlow()); // Cf(v,u) = C(v,u) - f(v,u)

	//	u = p[u];
	//}
	/////////////////////////////////////////////////

	vertex u = m_T;
	list<neighbor>::iterator itrG, itrRG;
	int edgeInGcap, edgeInGflow, negEdgeInGcap, negEdgeInGflow;

	//while (p[u] != NULL)
	//{
	//	list<neighbor>* AdjListG = G.SetAdjList(p[u]);
	//	itrG = AdjListG->begin();
	//	while (AdjListG->end() != itrG)
	//	{
	//		if (itrG->first == u)
	//		{
	//			edgeInGcap = itrG->second.GetCap();
	//			edgeInGflow = itrG->second.GetFlow();
	//			negEdgeInGcap = itrG->second.GetNegEdge()->GetCap();
	//			negEdgeInGflow = itrG->second.GetNegEdge()->GetFlow();
	//			break;
	//		}
	//		++itrG;
	//	}

	//	list<neighbor>* AdjListRG = RG.SetAdjList(p[u]);
	//	itrRG = AdjListRG->begin();
	//	while (AdjListRG->end() != itrRG)
	//	{
	//		if (itrRG->first == u)
	//		{
	//			itrRG->second.SetCap(edgeInGcap - edgeInGflow);
	//			itrRG->second.GetNegEdge()->SetCap(negEdgeInGcap - negEdgeInGflow);
	//			break;
	//		}
	//		++itrRG;
	//	}

	//	u = p[u];
	//}
	/////////////////////////////////////////////////////////////////////////////

	list<neighbor>::iterator itrPU;
	list<neighbor>::iterator itrU;

	while (p[u] != 0)
	{
		list<neighbor>* AdjListG = G->SetAdjList(p[u]);
		itrG = AdjListG->begin();
		while (AdjListG->end() != itrG)
		{
			if (itrG->first == u)
			{
				edgeInGcap = itrG->second.GetCap();
				edgeInGflow = itrG->second.GetFlow();
				negEdgeInGcap = itrG->second.GetNegEdge()->GetCap();
				negEdgeInGflow = itrG->second.GetNegEdge()->GetFlow();
				break;
			}
			++itrG;
		}

		list<neighbor>* AdjListPU = RG->SetAdjList(p[u]);
		itrPU = AdjListPU->begin();
		list<neighbor>* AdjListU = RG->SetAdjList(u);
		itrU = AdjListU->begin();

		while (AdjListPU->end() != itrPU)
		{
			if (itrPU->first == u)
			{
				itrPU->second.SetCap(edgeInGcap - edgeInGflow);
				break;
			}

			++itrPU;
		}

		while (AdjListU->end() != itrU)
		{
			if (itrU->first == p[u])
			{
				itrU->second.SetCap(negEdgeInGcap - negEdgeInGflow);
				break;
			}

			++itrU;
		}

		u = p[u];
	}



}

void FlowNetwork::updatePathInGraph(Graph G, list<Edge*>* P, int CfP)
{
	///////////////////////////////////////////////////////////////////////////////////

	//int newFlow;
	//vertex u = m_T;
	//list<neighbor> AdjList;
	//Edge* edgePtr;
	//while (p[u] != NULL)
	//{
	//	list<neighbor>* AdjListggggggg = m_Graph.SetAdjList(p[u]);       best one so far
	//	for (auto i : *AdjListggggggg)
	//	{
	//		if (i.first == u)
	//		{
	//			newFlow = i.second.GetFlow() + CfP;
	//			i.second.SetFlow(newFlow);
	//			i.second.GetNegEdge()->SetFlow(-newFlow);
	//			break;
	//		}

	//	}
	//	u = p[u];
	//}



	int newFlow;
	vertex u = m_T;
	list<neighbor>::iterator itrPU;
	list<neighbor>::iterator itrU;

	while (p[u] != 0)
	{
		list<neighbor>* AdjListPU = m_Graph.SetAdjList(p[u]);
		itrPU = AdjListPU->begin();
		list<neighbor>* AdjListU = m_Graph.SetAdjList(u);
		itrU = AdjListU->begin();

		while (AdjListPU->end() != itrPU)
		{
			if (itrPU->first == u)
			{
				newFlow = itrPU->second.GetFlow() + CfP;
				itrPU->second.SetFlow(newFlow);
				//Edge* e = itr->second.GetNegEdge();
				//e->SetFlow(-newFlow);
				//// itr->second.GetNegEdge()->SetFlow(-newFlow);
				break;
			}

			++itrPU;
		}

		while (AdjListU->end() != itrU)
		{
			if (itrU->first == p[u])
			{
				itrU->second.SetFlow(-newFlow);
				//Edge* e = itr->second.GetNegEdge();
				//e->SetFlow(-newFlow);
				//// itr->second.GetNegEdge()->SetFlow(-newFlow);
				break;
			}

			++itrU;
		}

		u = p[u];
	}
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

	while (p[u] != 0)
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
}

void FlowNetwork::findPathInGraph(Graph G, list<Edge*> *P, vertex s, vertex t)
{
	vertex u = t;
	list<neighbor> AdjList;
	Edge* edgePtr;

	while (p[u] != 0)
	{
		edgePtr = &G.GetEdgePtr(p[u], u);
		P->push_front(edgePtr);
		u = p[u];
	}
}

void FlowNetwork::BFS(Graph G, vertex s)
{
	vertex u;
	list<neighbor> AdjList;
	queue<vertex> Q;
	int amountOfVertices = G.GetAmountOfVertices();
	//int max = numeric_limits<int>::max();
	int max = INT8_MAX;

	for(int i = 1 ; i <= amountOfVertices; i++)
	{
		d[i] = max; // infinity
		p[i] = 0;
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
				if (d[v.first] == max) // infinity
				{
					d[v.first] = d[u] + 1;
					p[v.first] = u;
					Q.push(v.first);
				}
			}
		}
	}

	
}

void FlowNetwork::Dijkstra(Graph G, vertex s)
{
	PriorityQueue Q;
	Pair u;
	vertex v;
	int Wuv, minCap;
	list<neighbor>::iterator itrU;
	InitDijkstra(G, &d, &p, s);
	Edge* e = (Edge*)malloc(sizeof(Edge));
	Q.BuildPriorityQueue(G.GetAmountOfVertices(), d);

	while (!Q.IsEmpty())
	{
		u = Q.DeleteMax();
		list<neighbor>* AdjListU = m_Graph.SetAdjList(u.ver);
		itrU = AdjListU->begin();

		while (AdjListU->end() != itrU)
		{
			if (itrU->second.GetCap() != 0)
			{
				v = itrU->first;
				*e = G.GetEdgePtr(u.ver, v);
				Wuv = e->GetCap();

				if (u.ver == m_S)
				{
					minCap = Wuv;
				}
				else
				{
					minCap = min(d[u.ver], Wuv);
				}
				

				if (minCap > d[v])
				{
					d[v] = minCap;
					p[v] = u.ver;
					Q.IncreaseKey(v, d[v]);
				}
			}

			++itrU;
		}
	}

}

// Initiate the d and p vectors
void FlowNetwork::InitDijkstra(Graph G, vector<int>* d, vector<vertex>* p, vertex s)
{
	for (int v = 1; v <= G.GetAmountOfVertices(); v++)
	{
		d->at(v) = -1;
	}

	d->at(s) = 0;

	for (int v = 1; v <= G.GetAmountOfVertices(); v++)
	{
		p->at(v) = 0;
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