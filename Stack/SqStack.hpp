#pragma once
#include <iostream>

using namespace std;

template<class T>
class SqStack
{
public:
	int size() { return _size; }//����
	SqStack(int size)
	{
		_size = size;
		top = -1;
		elem = new T[size];

	}
	~SqStack()
	{
		delete[] elem;
	}

	bool Push(T const& e);//��ջ
	T Pop();//��ջ
	T& Top();//ȡջ��Ԫ��
	T& operator[](int r) { return elem[r]; }//����[]�������ʹջ����������������������

private:
	int _size;//����
	int top;//ջ��
	T* elem;//������ָ��
};

template<typename T>
bool SqStack<T>::Push(T const& e)
{
	if (top == _size) { return false; }
	elem[++top] = e;
	return true;
}

template<typename T>
T SqStack<T>::Pop()
{
	if (!size()) { exit(1); }
	return elem[top--];
}

template<typename T>
T& SqStack<T>::Top()
{
	return (*this)[this->top];
}