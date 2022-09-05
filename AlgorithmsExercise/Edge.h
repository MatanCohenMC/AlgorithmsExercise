#pragma once
using namespace std;
#include <iostream>
typedef int vertex;

class Edge
{
private:
	vertex m_Src;
	vertex m_Dest;
	int m_Cap;
	int m_Flow;
	Edge* m_NegEdge = (Edge*)malloc(sizeof(Edge)); // DON'T FORGET TO DELETE

public:
	Edge(int src, int dest, int cap, int flow = 0, Edge* negEdge = NULL);
	Edge CreateEdge(int src, int dest, int cap, int flow);
	vertex GetSrc() {return m_Src;}
	vertex GetDest() { return m_Dest; }
	int GetCap() { return m_Cap; }
	int GetFlow() { return m_Flow; }
	void SetFlow(int flow) { m_Flow = flow; }
	void SetNegEdge(Edge* e) { m_NegEdge = e; }
	Edge* GetNegEdge() { return m_NegEdge; }
	void SetCap(int cap) { m_Cap = cap; }
	void PrintEdge();
};