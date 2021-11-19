#pragma once
#include "Vector_Include.h"
template <typename T>
int Vector<T>::remove(Rank left, Rank right)		//O(n-right)
{
	if (left == right)
	{
		return 0;//出于效率考虑，单独处理退化情况
	}
	
	while (right < _size)
	{
		_elem[left++] = _elem[right++];// [right，_size) 顺次前移 right-left 位
	}
	_size = left;//更新规模
	shrink();//若有必要，缩容

	return right - left;//返回被删除元素的数目
}

template <typename T> 
T Vector<T>::remove(Rank r) 
{ 
	//删除向量中秩为r的元素，0 <= r < size
	T e = _elem[r]; //备份被删除元素
	remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
	return e; //返回被删除元素
}