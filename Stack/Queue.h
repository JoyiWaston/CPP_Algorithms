#pragma once
//����FIFO
//enqueue/dequeue
#include "W:\\C++_Workspace\\CPP_Algorithms\\List\\List.hpp"

template <typename T>
class Queue : public List<T>
{
public://size��empty����
	void enqueue(T const& e)
	{
		insertAsLast(e);//���
	}

	void dequeue(T const& e)
	{
		return remove(first());//����
	}
	
	T& front()
	{
		return first()->data;//����
	}
};