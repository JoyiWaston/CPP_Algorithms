#pragma once
#include "Vector_Include.h"

template <typename T>
int Vector<T>::disordered() const
{
	int count = 0;//������
	for (int i = 1; i < _size; i++)//��һ����������Ԫ��
	{
		n += (_elem[i - 1] > _elem[i]);//���������
	}
	return n;//���������ҽ���n = 0
}//��ֻ���ж��Ƿ��������״����������֮�󼴿���ֹ