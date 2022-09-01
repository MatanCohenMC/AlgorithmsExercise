#pragma once
using namespace std;
#include <iostream>
#include <vector>

typedef int vertex;

typedef struct
{
	int priority;
	vertex ver;
}Pair;

class PriorityQueue
{
private:
	vector<Pair> m_MaxHeap;
	static int Parent(int node) { return ((node - 1) / 2); }
	static int Left(int node) { return (2 * node + 1); }
	static int Right(int node) { return (2 * node + 2); }

public:
	PriorityQueue() { m_MaxHeap.clear(); }
	void BuildPriorityQueue(int amountOfVertices, vector<int> d);
	void DownFixHeap(int node);
	Pair DeleteMax();
	void Insert(Pair item);
	void PrintQueue();
	void Swap(int index1, int index2);
};