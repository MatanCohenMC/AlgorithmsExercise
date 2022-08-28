#pragma once
using namespace std;
#include <vector>
#include <iostream>
#include <vector>
#include <list>
#include "Edge.h"


struct Vertex {
	int vertex;
};

typedef pair<int, Edge> neighbor;

class Graph
{
private:
	int amountOfVertices = 0;
	vector<list<Vertex>> adjLists;

public:
	void MakeEmptyGraph(int n);
	list<Vertex> GetAdjList(int u);
	void AddEdge(int u, int v, int c);
	void RemoveEdge(int u, int v);
};

