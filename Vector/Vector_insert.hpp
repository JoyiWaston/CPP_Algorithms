#pragma once
#include "Vector_Include.h"

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)		//O(n-r)
{
	expand();//���б�Ҫ������
	for (int i = _size; i > r; i--)//�Ժ���ǰ
	{
		_elem[i] = _elem[i - 1];//���Ԫ��˳�κ���һ����Ԫ
	}
	_elem[r] = e;//������Ԫ��
	_size++;//��������

	return r;//������
}