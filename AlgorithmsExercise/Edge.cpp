#include "Edge.h"

Edge::Edge(int src, int dest, int weight, int flow)
{
	m_Src = src;
	m_Dest = dest;
	m_Weight = weight;
	m_Flow = flow;
}