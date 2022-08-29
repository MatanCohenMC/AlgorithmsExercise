using namespace std;
#include <iostream>
#include <stdlib.h>
#include "Graph.h"

void initParams(int* n, int* m, int* s, int* t);
void initListOfEdges(int n, int m, list<Edge>* listOfEdges);
void invalidInput();
int getWholePositiveNum();
int getWholePositiveOrZeroNum();
bool ifNumIsWhole(float num);
int getNumInRange(int numOfVertices);


int main()
{
	int n, m;
	vertex s, t;
	initParams(&n, &m, &s, &t);
	list<Edge> listOfEdges;
	initListOfEdges(n,m, &listOfEdges);

	// print to check list ///////
	cout << "List of edges = { ";
	for (Edge e : listOfEdges) {
		cout << "(" << e.getSrc() << ", " << e.getDest() << ", " << e.getCap() << ", " << e.getFlow() << ") , ";
	}
	cout << "};\n";
	//////////////////////////////

	// create flow network


	
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
void initListOfEdges(int n,int m, list<Edge>* listOfEdges)
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

		(*listOfEdges).push_back(newEdge);
	}
}
