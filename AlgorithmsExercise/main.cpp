/*
 
	This program solves the maximum flow problem in two different ways.
	The problem is finding a feasible flow through a flow network that
	obtains the maximum possible flow rate.

	------INSTRUCTIONS-----
	The program gets the amount of vertices.

	The program gets the number of edges.

	The program gets the start vertex.

	The program gets the end vertex.

	The program gets the edges one by one, each edge has it's source vertex, destination vertex and it's capacity.

	The program uses 2 functions to solve this problem:
	1. Using the BFS algorithm.
	2. Using the Dijkstra algorithm.

*/

using namespace std;
#include <iostream>
#include "Graph.h"
#include "FlowNetwork.h"

void initParams(int* n, int* m, int* s, int* t);
void initListOfEdges(int n, int m, list<Edge>* listOfEdges, Graph* graph);
void invalidInput();
int getWholePositiveNum();
int getWholePositiveOrZeroNum();
bool ifNumIsWhole(float num);
int getNumInRange(int numOfVertices);
void printMinCut(vector<vertex> S, vector<vertex> T);
void freeEdges(list<Edge>* listOfEdges);

int main()
{
	int n, m, maxFlow;
	vertex s, t;
	Graph G;
	vector<vertex> S;
	vector<vertex> T;
	S.clear(); T.clear();
	initParams(&n, &m, &s, &t);
	G.MakeEmptyGraph(n);
	list<Edge> listOfEdges;
	initListOfEdges(n,m, &listOfEdges, &G);
	Graph G2 = G;
	FlowNetwork flowNetWorkForBFS(&G, s, t);
	FlowNetwork flowNetWorkForDijkstra(&G2, s, t);

	maxFlow = flowNetWorkForBFS.FFbyBFS(&S, &T);
	cout << "BFS Method:\n";
	cout << "Max flow = " << maxFlow << "\n";
	printMinCut(S,T);
	S.clear(); T.clear();
	maxFlow = flowNetWorkForDijkstra.FFbyDijkstra(s,t, &S, &T);
	cout << "Greedy Method:\n";
	cout << "Max flow = " << maxFlow << "\n";
	printMinCut(S, T);
	freeEdges(&listOfEdges);
}

// get the number of vertices, number of edges, the number representing s and the number representing s
void initParams(int* n, int* m, vertex* s, vertex* t)
{
	// cout << "Please enter the number of vertices.\n";
	*n = getWholePositiveOrZeroNum();
	// cout << "Please enter the number of edges.\n";
	*m = getWholePositiveOrZeroNum();
	// cout << "Please enter the number that represent S.\n";
	*s = getNumInRange(*n);
	// cout << "Please enter the number that represent T.\n";
	*t = getNumInRange(*n);
}

// report "invalid input" and exit program
void invalidInput()
{
	cout << "Invalid input.\n";
	exit(1);
}

// Get a whole number that is zero or greater
int getWholePositiveOrZeroNum()
{
	float num;

	cin >> num;
	if (num < 0 || !ifNumIsWhole(num))
	{
		invalidInput();
	}

	return num;
}

// Get a whole and Positive number
int getWholePositiveNum()
{
	float num;

	cin >> num;
	if (num < 1 || !ifNumIsWhole(num))
	{
		invalidInput();
	}

	return num;
}

// Get a whole number
bool ifNumIsWhole(float num)
{
	bool flag = false;
	int intNum = num;

	if(num - intNum == 0)
	{
		flag = true;
	}

	return flag;
}

// Get a whole number between 1 to n
int getNumInRange(int numOfVertices)
{
	float num;

	cin >> num;
	if (num > numOfVertices || num < 1 || !ifNumIsWhole(num))
	{
		invalidInput();
	}

	return num;
}

// Get the Edges
void initListOfEdges(int n,int m, list<Edge>* listOfEdges, Graph* graph)
{
	int cap;
	vertex src, dest;

	for (int i=0 ; i < m ; i++)
	{
		// cout << "Please enter the edge parameters (src, dest, weight):\n";
		src = getNumInRange(n);
		dest = getNumInRange(n);
		cap = getWholePositiveNum();
		Edge newEdge(src, dest, cap, 0);

		graph->AddEdge(src, dest, cap);
		(*listOfEdges).push_back(newEdge);
	}

	graph->AddNegativeEdges();
}

// Print the minimum cut
void printMinCut(vector<vertex> S, vector<vertex> T)
{
	int countI = 0;
	int sSize = S.size();
	int tSize = T.size();

	cout << "Min cut: S = ";
	for (auto i : S)
	{
		countI++;
		cout << i;
		if (countI < sSize)
		{
			cout << ", ";
		}
		else
		{
			cout << ". ";
		}
	}

	countI = 0;
	cout << "T = ";
	for (auto i : T)
	{
		countI++;
		cout << i;
		if (countI < tSize)
		{
			cout << ", ";
		}
	}

	cout << "\n";
}

// Free all the edges
void freeEdges(list<Edge>* listOfEdges)
{
	for (auto i : *listOfEdges)
	{
		i.FreeEdge();
	}
}