#pragma once
#include <iostream>

using namespace std;

template<class T>
class SqStack
{
public:
	int size() { return _size; }//容量
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

	bool Push(T const& e);//入栈
	T Pop();//出栈
	T& Top();//取栈顶元素
	T& operator[](int r) { return elem[r]; }//重载[]运算符，使栈可以用数组索引访问数据

private:
	int _size;//容量
	int top;//栈顶
	T* elem;//数据域指针
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