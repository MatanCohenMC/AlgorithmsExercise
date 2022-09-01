#pragma once
#include "Graph.h"
#include "PriorityQueue.h"
#include <queue>


class FlowNetwork
{
private:
	Graph m_Graph;
	vertex m_S , m_T;

public:
	FlowNetwork(Graph G, vertex s, vertex t) { m_Graph = G, m_S = s, m_T = t; }

	void BFS(Graph G, vertex s);
	void Dijkstra(Graph G, int weight, vertex s);
	void Init(Graph G, vector<int>* d, vector<vertex>* p, vertex s);
	// FFbyBFS
	// FFbyDyxtra

};

