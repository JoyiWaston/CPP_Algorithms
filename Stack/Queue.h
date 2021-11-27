#pragma once
//队列FIFO
//enqueue/dequeue
#include "W:\\C++_Workspace\\CPP_Algorithms\\List\\List.hpp"

template <typename T>
class Queue : public List<T>
{
public://size与empty沿用
	void enqueue(T const& e)
	{
		insertAsLast(e);//入队
	}

	void dequeue(T const& e)
	{
		return remove(first());//出队
	}
	
	T& front()
	{
		return first()->data;//队首
	}
};