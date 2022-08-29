#include "PriorityQueue.h"

// Create a new priority queue
void PriorityQueue::BuildPriorityQueue(vector<vertex> verArr, vector<int> d)
{
	m_MaxHeap.resize(verArr.size());
	m_MaxHeap.clear(); // not nessecery

	for (int i = 1; i < verArr.size(); ++i)
	{
		m_MaxHeap[i].priority = d[i];
		m_MaxHeap[i].ver = verArr[i];
	}

	for (int i = m_MaxHeap.size()/2 - 1; i >= 0; i--)
	{
		DownFixHeap(i);
	}
}

// Place the item in his right place in the priority queue
void PriorityQueue::DownFixHeap(int index)
{
	int left = Left(index);
	int right = Right(index);
	int max = index;

	if (left < m_MaxHeap.size() && m_MaxHeap[left].priority >= m_MaxHeap[index].priority)
	{
		max = left;
	}
	if (right < m_MaxHeap.size() && m_MaxHeap[right].priority >= m_MaxHeap[max].priority)
	{
		max = right;
	}
	if (max != index)
	{
		swap(index, max);
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