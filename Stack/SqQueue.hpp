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
		elem = new T[size];//����ռ�
		//�ж�����ռ����ʧ�ܣ����˳�
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
	int count;//Ԫ�ظ���
	int maxSize;//�����������
	int front;//����
	int rear;//��β
	T* elem;//����ָ��
};

template<typename T>
bool SqQueue<T>::enqueue(T const& e)
{
	if (count == maxSize) { return false; }//�ж϶����Ƿ�����
	elem[rear] = e;//�����ݲ����β
	rear = (rear + 1) % maxSize;//�����βָ�룬Ϊ��ʡ�ռ䣬����ȡģ��ʽ�����βλ��
	count++;//Ԫ������һ
	return true;
}

template<typename T>
T SqQueue<T>::dequeue()
{
	if (count == 0) { exit(1); }//�ж��Ƿ�ӿ�
	T temp = elem[front];//ȥ������Ԫ��
	front = (front + 1) % maxSize;//�����µĶ���λ�ã�Ϊ��ʡ�ռ䣬��ȡģ��
	count--;
	return temp;
}