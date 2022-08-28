#pragma once

class Edge
{
private:
	int m_Src;
	int m_Dest;
	int m_Weight;
	int m_Flow = 0;

public:
	Edge(int src, int dest, int weight, int flow);
	void setFlow(int src);
	int getFlow();

};