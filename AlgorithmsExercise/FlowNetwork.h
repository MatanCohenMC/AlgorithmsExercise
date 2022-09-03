#pragma once
#include "Graph.h"
#include "PriorityQueue.h"
#include <queue>


class FlowNetwork
{
private:
	Graph m_Graph;
	vertex m_S , m_T;
	vector<int> d;
	vector<vertex> p;

public:
	FlowNetwork(Graph* G, vertex s, vertex t);
	void BFS(Graph G, vertex s);
	void Dijkstra(Graph G, int weight, vertex s);
	void Init(Graph G, vector<int>* d, vector<vertex>* p, vertex s);
	int FFbyBFS();
	// FFbyDyxtra
	void findPathInResidualGraph(list<Edge> *P, vertex s, vertex t);
	int findResidualCap(list<Edge> P);
};

