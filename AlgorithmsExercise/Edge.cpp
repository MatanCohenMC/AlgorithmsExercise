#include "Edge.h"

Edge::Edge(int src, int dest, int cap, int flow)
{
	m_Src = src;
	m_Dest = dest;
	m_Cap = cap;
	m_Flow = flow;
}