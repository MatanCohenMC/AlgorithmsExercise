#include "Graph.h"

// Make an empty graph
void Graph::MakeEmptyGraph(int n)
{
	m_AmountOfVertices = n;
	m_AdjLists.resize(n+1);
	for (int i = 0; i <= n; i++)
	{
		m_AdjLists[i].clear();
	}
}

// Get the vertex "u" neighbors list
list<neighbor> Graph::GetAdjList(vertex u)
{
	return m_AdjLists[u];
}

list<neighbor>* Graph::SetAdjList(vertex u)
{
	return &m_AdjLists[u];
}

// Add new edge to the graph
void Graph::AddEdge(vertex u, vertex v, int c)
{
	Edge newEdge(u, v, c, 0);
	neighbor newNeighbor(v, newEdge);
	
	m_AdjLists[u].push_back(newNeighbor);
}

Edge& Graph::GetEdgePtr(vertex u, vertex v)
{
	list<neighbor> AdjList = m_AdjLists[u];
	Edge* edge = nullptr;

	for (auto i : AdjList)
	{
		if (i.first == v)
		{
			edge = &(i.second);
			return *edge;
		}
	}
}

// Remove the edge (u,v) from the graph
void Graph::RemoveEdge(vertex u, vertex v)
{
	list<neighbor>::iterator itr;
	itr = m_AdjLists[u].begin();

	while (m_AdjLists[u].end() != itr)
	{
		if (itr->first == v)
		{
			m_AdjLists[u].erase(itr);
			break;
		}

		++itr;
	}
}

// Print the graph
void Graph::PrintGraph()
{
	for (int i = 1; i <= m_AmountOfVertices; i++)
	{
		cout << "[" << i << "] -> ";
		PrintAdjList(i);
	}
}

// Print the Adj list
void Graph::PrintAdjList(vertex u)
{
	for (auto& i : m_AdjLists[u]) 
	{
		cout << "{" << i.first << ",";
		(i.second).PrintEdge();
		cout << "} , ";
	}

	cout << "\b\b" << "|";
	cout << "\n";
}


void Graph::AddNegativeEdges()
{
	bool negEdgeExist = false;
	list<neighbor> AdjList;
	list<neighbor>::iterator itrV;
	list<neighbor>::iterator itrU;
	
	for (int i = 1; i <= m_AmountOfVertices; i++)
	{
		itrV = m_AdjLists[i].begin();
		while (m_AdjLists[i].end() != itrV)
		{
			itrU = m_AdjLists[itrV->first].begin();
			while (m_AdjLists[itrV->first].end() != itrU)
			{
				if (itrU->first == itrV->second.GetSrc())
				{
					itrV->second.SetNegEdge(&(itrU->second));
					itrU->second.SetNegEdge(&(itrV->second));
					negEdgeExist = true;
				}

				++itrU;
			}

			itrU = m_AdjLists[itrV->first].begin();
			if (negEdgeExist == false)
			{
				Edge newEdge(itrV->second.GetDest(), itrV->second.GetSrc(), 0, 0);
				neighbor newNeighbor(itrV->second.GetSrc(), newEdge);
				m_AdjLists[itrV->first].push_back(newNeighbor);

				while (m_AdjLists[itrV->first].end() != itrU)
				{
					if (itrU->first == itrV->second.GetSrc())
					{
						itrV->second.SetNegEdge(&(itrU->second));
						itrU->second.SetNegEdge(&(itrV->second));
					}

					++itrU;
				}
			}

			negEdgeExist = false;

			++itrV;
		}
	}
	




	//bool negEdgeExist = false;
	//list<neighbor> AdjList;

	//for (int i = 1; i <= m_AmountOfVertices; i++)
	//{
	//	for (auto v : m_AdjLists[i])
	//	{
	//		for (auto u : m_AdjLists[v.first])
	//		{
	//			if (u.first == v.second.GetSrc())
	//			{
	//				v.second.SetNegEdge(&(u.second));
	//				u.second.SetNegEdge(&(v.second));
	//				negEdgeExist = true;
	//			}
	//		}

	//		if (negEdgeExist == false)
	//		{
	//			Edge newEdge(v.second.GetDest(), v.second.GetSrc(), 0, 0);
	//			neighbor newNeighbor(v.second.GetSrc(), newEdge);
	//			m_AdjLists[v.first].push_back(newNeighbor);

	//			for (auto u : m_AdjLists[v.first])
	//			{
	//				if (u.first == v.second.GetSrc())
	//				{
	//					v.second.SetNegEdge(&(u.second));
	//					u.second.SetNegEdge(&(v.second));
	//				}
	//			}
	//		}

	//		negEdgeExist = false;
	//	}
	//}

	//this->PrintGraph();                 // CHECKING	
	//cout << "\n";
	//int i;
	//for (i = 1; i <= this->GetAmountOfVertices() ; i++)
	//{
	//	for (auto v : m_AdjLists[i])
	//	{
	//		v.second.PrintEdge();
	//		cout << " - ";
	//		v.second.GetNegEdge()->PrintEdge();
	//		cout << "\n";
	//	}
	//}
	
}