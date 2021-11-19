#pragma once
#include "Vector_Include.h"

template <typename T>
int Vector<T>::disordered() const
{
	int count = 0;//计数器
	for (int i = 1; i < _size; i++)//逐一检查各对相邻元素
	{
		n += (_elem[i - 1] > _elem[i]);//逆序则计数
	}
	return n;//向量有序当且仅当n = 0
}//若只需判断是否有序，则首次遇到逆序对之后即可终止