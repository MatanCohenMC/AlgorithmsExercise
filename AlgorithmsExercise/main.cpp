using namespace std;
#include <iostream>
#include "Graph.h"
#include "PriorityQueue.h"
#include  "FlowNetwork.h"

void initParams(int* n, int* m, int* s, int* t);
void initListOfEdges(int n, int m, list<Edge>* listOfEdges, Graph* graph);
void invalidInput();
int getWholePositiveNum();
int getWholePositiveOrZeroNum();
bool ifNumIsWhole(float num);
int getNumInRange(int numOfVertices);
void printMinCut(vector<vertex> S, vector<vertex> T);


int main()
{
	int n, m, maxFlow;
	vertex s, t;
	Graph G;
	vector<vertex> S;
	vector<vertex> T;


	initParams(&n, &m, &s, &t);
	G.MakeEmptyGraph(n);
	list<Edge> listOfEdges; // not really needed
	initListOfEdges(n,m, &listOfEdges, &G);
	G.PrintGraph(); // JUST FOR CHECKING


	//cout << "\n";
	//int i;
	//for (i = 1; i <= n; i++)
	//{
	//	for (auto v : G.GetAdjList(i))
	//	{
	//		v.second.PrintEdge();
	//		cout << " - ";
	//		v.second.GetNegEdge()->PrintEdge();
	//		cout << "\n";
	//	}
	//}
	Graph G2 = G;

	FlowNetwork flowNetWorkForBFS(&G, s, t);
	FlowNetwork flowNetWorkForDijkstra(&G2, s, t);

	maxFlow = flowNetWorkForBFS.FFbyBFS(&S, &T);
	cout << "BFS Methhod:\n";
	cout << "Max flow = " << maxFlow << "\n";
	printMinCut(S,T);

	S.clear(); T.clear();
	
	maxFlow = flowNetWorkForDijkstra.FFbyDijkstra(s,t, &S, &T);
	cout << "Greedy Methhod:\n";
	cout << "Max flow = " << maxFlow << "\n";
	printMinCut(S, T);




	// Test queue
	/*PriorityQueue Q;
	vector<int> d = { -1, 7, 2 ,5, 1, 3 };
	Q.BuildPriorityQueue(5, d);
	Q.PrintQueue();
	*/


	// print to check list ///////
	/*cout << "List of edges = { ";
	for (Edge e : listOfEdges) {
		cout << "(" << e.GetSrc() << ", " << e.GetDest() << ", " << e.GetCap() << ", " << e.GetFlow() << ") , ";
	}
	cout << "};\n";*/
	//////////////////////////////


	
}

// get the number of vertices, number of edges, the number representing s and the number representing s
void initParams(int* n, int* m, vertex* s, vertex* t)
{
	cout << "Please enter the number of vertices.\n";
	*n = getWholePositiveOrZeroNum();
	cout << "Please enter the number of edges.\n";
	*m = getWholePositiveOrZeroNum();
	cout << "Please enter the number that represent S.\n";
	*s = getNumInRange(*n);
	cout << "Please enter the number that represent T.\n";
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
	return floor(num) == num;
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
		cout << "Please enter the edge parameters (src, dest, weight):\n";
		src = getNumInRange(n);
		dest = getNumInRange(n);
		cap = getWholePositiveNum();
		Edge newEdge(src, dest, cap, 0);

		
		graph->AddEdge(src, dest, cap); // add to graph

		(*listOfEdges).push_back(newEdge); // add to edges list
	}

	graph->AddNegativeEdges();
}

void printMinCut(vector<vertex> S, vector<vertex> T)
{
	cout << "Min cut: S = ";
	for (auto i : S)
	{
		cout << i << ",";
	}
	cout << "\b" << ". ";
	cout << "T = ";
	for (auto i : T)
	{
		cout << i << ",";
	}
	cout << "\b" << ". " << "\n";
}