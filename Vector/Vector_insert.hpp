#pragma once
#include "Vector_Include.h"

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)		//O(n-r)
{
	expand();//如有必要，扩容
	for (int i = _size; i > r; i--)//自后向前
	{
		_elem[i] = _elem[i - 1];//后继元素顺次后移一个单元
	}
	_elem[r] = e;//置入新元素
	_size++;//更新容量

	return r;//返回秩
}