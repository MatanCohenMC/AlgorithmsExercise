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

// Ford Fulkerson algorithm using BFS
int FlowNetwork::FFbyBFS(vector<vertex> *S, vector<vertex> *T)
{
	int maxFlow = 0;
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
		int CfP = findResidualCap(residualGraph);
		updatePathInGraph(CfP);
		updatePathInResidualGraph(&m_Graph, &residualGraph);
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
		int CfP = findResidualCap(residualGraph);
		updatePathInGraph(CfP);
		updatePathInResidualGraph(&m_Graph, &residualGraph);
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

void FlowNetwork::updatePathInResidualGraph(Graph* G, Graph* RG)
{
	vertex u = m_T;
	list<neighbor>::iterator itrG, itrRG, itrPU, itrU;
	int edgeInGcap, edgeInGflow, negEdgeInGcap, negEdgeInGflow;

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

void FlowNetwork::updatePathInGraph(int CfP)
{
	int newFlow = 0;
	vertex u = m_T;
	list<neighbor>::iterator itrPU, itrU;

	while (p[u] != 0)
	{
		list<neighbor>* AdjListPU = m_Graph.SetAdjList(p[u]);
		list<neighbor>* AdjListU = m_Graph.SetAdjList(u);
		itrPU = AdjListPU->begin();
		itrU = AdjListU->begin();

		while (AdjListPU->end() != itrPU)
		{
			if (itrPU->first == u)
			{
				newFlow = itrPU->second.GetFlow() + CfP;
				itrPU->second.SetFlow(newFlow);
				break;
			}

			++itrPU;
		}

		while (AdjListU->end() != itrU)
		{
			if (itrU->first == p[u])
			{
				itrU->second.SetFlow(-newFlow);
				break;
			}

			++itrU;
		}

		u = p[u];
	}
}

int FlowNetwork::findResidualCap(Graph G)
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

// BFS algorithm
void FlowNetwork::BFS(Graph G, vertex s)
{
	vertex u;
	list<neighbor> AdjList;
	queue<vertex> Q;
	int amountOfVertices = G.GetAmountOfVertices();
	int max = INT8_MAX;

	for(int i = 1 ; i <= amountOfVertices; i++)
	{
		d[i] = max; // Infinity
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
				if (d[v.first] == max) // Infinity
				{
					d[v.first] = d[u] + 1;
					p[v.first] = u;
					Q.push(v.first);
				}
			}
		}
	}
}

// Dijkstra algorithm
void FlowNetwork::Dijkstra(Graph G, vertex s)
{
	PriorityQueue Q;
	Pair u;
	vertex v;
	int Wuv, minCap;
	list<neighbor>::iterator itrU;
	Edge* e = (Edge*)malloc(sizeof(Edge));

	InitDijkstra(G, &d, &p, s);
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

	delete e;
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