#pragma once

class Edge
{
private:
	int m_Src;
	int m_Dest;
	int m_Cap;
	int m_Flow = 0;

public:
	Edge(int src, int dest, int cap, int flow);
	Edge createEdge(int src, int dest, int cap, int flow);
	int getSrc() {return m_Src;}
	int getDest() { return m_Dest; }
	int getCap() { return m_Cap; }
	int getFlow() { return m_Flow; }
	void setFlow(int flow) { m_Flow = flow; }

};