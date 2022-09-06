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
	void Dijkstra(Graph G, vertex s);
	void InitDijkstra(Graph G, vector<int>* d, vector<vertex>* p, vertex s);
	int FFbyBFS(vector<vertex>* S, vector<vertex>* T);
	int FFbyDijkstra(vertex s, vertex t, vector<vertex>* S, vector<vertex>* T);
	void findPathInGraph(Graph G, list<Edge*>* P, vertex s, vertex t);
	int findResidualCap(Graph G, list<Edge*> P);
	void updatePathInGraph(Graph G, list<Edge*>* P, int CfP);
	void updatePathInResidualGraph(Graph *G, Graph *RG, list<Edge*>* P, list<Edge*>* RP);
	void printD();
};

