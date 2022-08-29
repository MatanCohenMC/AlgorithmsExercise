#include "Edge.h"

// Create new edge
Edge::Edge(vertex src, vertex dest, int cap, int flow)
{
	m_Src = src;
	m_Dest = dest;
	m_Cap = cap;
	m_Flow = flow;
}

// Print edge
void Edge::PrintEdge()
{
	cout << "(" << m_Src << "," << m_Dest << "," << m_Cap << "," << m_Flow << ")";
}