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
	int m_Flow = 0;

public:
	Edge(int src, int dest, int cap, int flow);
	Edge CreateEdge(int src, int dest, int cap, int flow);
	vertex GetSrc() {return m_Src;}
	vertex GetDest() { return m_Dest; }
	int GetCap() { return m_Cap; }
	int GetFlow() { return m_Flow; }
	void SetFlow(int flow) { m_Flow = flow; }
	void PrintEdge();
};