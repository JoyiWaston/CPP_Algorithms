#pragma once
#include "Vector_Include.h"
template <typename T>//TΪ�������ͣ��������ظ�ֵ������"="
void Vector<T>::copyFrom(T const* A,Rank left,Rank right)
{
	_elem = new T[_capacity = 2 * (left - right)];//����ռ�
	//��ģ����
	for (_size = 0; left < right; _size++, left++)//A[left,right)��Ԫ����һ���
	{
		_elem[_size] = A[left];//������ _elem[0,right-left)
	}
}
//����ʱ�� = O(right-left)