#pragma once
#include "W:\\C++_Workspace\\CPP_Algorithms\\Vector\\Vector.hpp"

template <typename T>
class Stack : public Vector<T>//����������
{
public://size(),empty()���������Žӿھ���ֱ��ʹ��
	void push(T const& e) { insert(size(), e); }//��ջ
	T pop() { return remove(size() - 1); }//��ջ
	T& top() { return (*this)[size() - 1]; }//ȡջ��Ԫ��
};//��������/ĩ��Ϊջ��/�������ߵ�֮���أ�