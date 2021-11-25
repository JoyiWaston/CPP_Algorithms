#pragma once
#include "W:\\C++_Workspace\\CPP_Algorithms\\Vector\\Vector.hpp"

template <typename T>
class Stack : public Vector<T>//由向量派生
{
public://size(),empty()及其他开放接口均可直接使用
	void push(T const& e) { insert(size(), e); }//入栈
	T pop() { return remove(size() - 1); }//出栈
	T& top() { return (*this)[size() - 1]; }//取栈顶元素
};//以向量首/末端为栈底/顶——颠倒之后呢？