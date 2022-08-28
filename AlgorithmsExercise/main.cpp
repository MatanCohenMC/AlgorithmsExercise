using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "Graph.h"

void init(int* n, int* m, int* s, int* t);
void initListOfEdges(int m);
void invalidInput();

int main()
{
	int n, m, s, t;
	init(&n, &m, &s, &t);
	list<Edge> listOfEdges;
	initListOfEdges(m);
	
}

void init(int* n, int* m, int* s, int* t)
{
	cout << "Please enter the number of vertices" << endl;
	cin >> *n;
	cout << "Please enter the number of edges" << endl;
	cin >> *m;
	cout << "Please enter the number that represent S" << endl;
	cin >> *s;
	cout << "Please enter the number that represent T" << endl;
	cin >> *t;
}

void initListOfEdges(int m)
{
	// not negative capacity
	// vertices from 1 to n
}

void invalidInput()
{
	cout << "Invalid input" << endl;
	exit(1);
}