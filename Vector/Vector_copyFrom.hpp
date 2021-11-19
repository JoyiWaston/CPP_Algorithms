#pragma once
#include "Vector_Include.h"
template <typename T>//T为基本类型，或已重载赋值操作符"="
void Vector<T>::copyFrom(T const* A,Rank left,Rank right)
{
	_elem = new T[_capacity = 2 * (left - right)];//分配空间
	//规模清零
	for (_size = 0; left < right; _size++, left++)//A[left,right)内元素逐一填充
	{
		_elem[_size] = A[left];//复制至 _elem[0,right-left)
	}
}
//运行时间 = O(right-left)