#include "PriorityQueue.h"

// Create a new priority queue
void PriorityQueue::BuildPriorityQueue(int amountOfVertices, vector<int> d)
{
	m_MaxHeap.resize(amountOfVertices);

	for (int i = 0; i < m_MaxHeap.size(); ++i)
	{
		m_MaxHeap[i].priority = d[i+1];
		m_MaxHeap[i].ver = i+1;
	}

	for (int i = m_MaxHeap.size()/2 - 1; i >= 0; i--)
	{
		DownFixHeap(i);
	}
}

// Place the item in his right place in the priority queue
void PriorityQueue::DownFixHeap(int node)
{
	int left = Left(node);
	int right = Right(node);
	int max;

	if (left < m_MaxHeap.size() && m_MaxHeap[left].priority > m_MaxHeap[node].priority)
	{
		max = left;
	}
	else
	{
		max = node;
	}

	if (right < m_MaxHeap.size() && m_MaxHeap[right].priority > m_MaxHeap[max].priority)
	{
		max = right;
	}

	if (max != node)
	{
		Swap(node, max);
		DownFixHeap(max);
	}
}

// Delete the max priority item in the priority queue
Pair PriorityQueue::DeleteMax()
{
	if (m_MaxHeap.empty())
	{
		cout << "wrong input\n";
		exit(1);
	}

	Pair max = m_MaxHeap[0];
	m_MaxHeap[0] = m_MaxHeap.back();
	m_MaxHeap.pop_back();
	DownFixHeap(0);
	return max;
}

// Insert new item to the priority queue
void PriorityQueue::Insert(Pair item)
{
	int i = m_MaxHeap.size();

	while((i > 0) && (m_MaxHeap[Parent(i)].priority < item.priority))
	{
		m_MaxHeap[i] = m_MaxHeap[Parent(i)];
		i = Parent(i);
	}

	m_MaxHeap[i] = item;
}

// Print the queue
void PriorityQueue::PrintQueue()
{
	for(int i = 0 ; i < m_MaxHeap.size() ; ++i)
	{
		cout << "[" << i << "]" << "(" << m_MaxHeap[i].ver << "," << m_MaxHeap[i].priority << ")\n";
	}
}

// Swap between two cells of the queue by index
void PriorityQueue::Swap(int index1, int index2)
{
	Pair tmp = m_MaxHeap[index1];
	m_MaxHeap[index1] = m_MaxHeap[index2];
	m_MaxHeap[index2] = tmp;
}

// Return TRUE if the queue is empty
bool PriorityQueue::IsEmpty()
{
	return m_MaxHeap.empty();
}

// Change the priority of the vertex v in the queue to d[v]
void PriorityQueue::IncreaseKey(vertex v, int dV)
{
	int i, j;
	for (i = 0; i < m_MaxHeap.size(); i++)
	{
		if (m_MaxHeap[i].ver == v)
		{
			m_MaxHeap[i].priority = dV;
			break;
		}
	}

	j = i;
	while ((j > 0) && (m_MaxHeap[Parent(j)].priority < dV))
	{
		Swap(Parent(j), j);
		j = Parent(j);
	}
}