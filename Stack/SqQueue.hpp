#pragma once
#include <iostream>

using namespace std;

template<class T>
class SqQueue
{
public:
	SqQueue(int size)
	{
		maxSize = size;
		front = 0;
		rear = 0;
		count = 0;
		elem = new T[size];//分配空间
		//判断如果空间分配失败，则退出
		if (elem == nullptr)
		{
			exit(1);
		}
	}
	~SqQueue()
	{
		delete[] elem;
	}

	bool enqueue(T const& e);
	T dequeue();

private:
	int count;//元素个数
	int maxSize;//队列最大容量
	int front;//队首
	int rear;//队尾
	T* elem;//数据指针
};

template<typename T>
bool SqQueue<T>::enqueue(T const& e)
{
	if (count == maxSize) { return false; }//判断队列是否已满
	elem[rear] = e;//将数据插入队尾
	rear = (rear + 1) % maxSize;//变更队尾指针，为节省空间，采用取模方式计算队尾位置
	count++;//元素数加一
	return true;
}

template<typename T>
T SqQueue<T>::dequeue()
{
	if (count == 0) { exit(1); }//判断是否队空
	T temp = elem[front];//去除队首元素
	front = (front + 1) % maxSize;//设置新的队首位置，为节省空间，用取模法
	count--;
	return temp;
}