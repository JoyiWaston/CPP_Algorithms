#pragma once
#include "Vector_Include.h"

template <typename T>
void Vector<T>::expand()//向量空间不足时扩充
{
	if (_size < _capacity)
	{
		return;
	}

	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//容量加倍		几何级数O（n）；		固定数值扩容	算术级数O(n^2) ;
	for (int i = 0; i < _size; i++)//复制原向量内容
	{
		_elem[i] = oldElem[i];	   //T为基本类型，或已重载赋值操作符'='
	}

	delete[] oldElem;//释放原空间
}