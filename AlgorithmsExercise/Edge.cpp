#include "Edge.h"

Edge::Edge(vertex src, vertex dest, int cap, int flow)
{
	m_Src = src;
	m_Dest = dest;
	m_Cap = cap;
	m_Flow = flow;
}