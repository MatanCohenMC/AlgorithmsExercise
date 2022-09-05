#pragma once
using namespace std;
#include <vector>
#include <iostream>
#include <vector>
#include <list>
#include "Edge.h"

typedef pair<vertex, Edge> neighbor;

class Graph
{
private:
	int m_AmountOfVertices = 0;
	vector<list<neighbor>> m_AdjLists;

public:
	void MakeEmptyGraph(int n);
	list<neighbor> GetAdjList(vertex u);
	list<neighbor>* SetAdjList(vertex u);
	void AddEdge(vertex u, vertex v, int c);
	Edge& GetEdgePtr(vertex u ,vertex v);
	void RemoveEdge(vertex u, vertex v);
	void PrintGraph();
	void PrintAdjList(vertex u);
	int GetAmountOfVertices() { return m_AmountOfVertices; }
	void AddNegativeEdges();
};

