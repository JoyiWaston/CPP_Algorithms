#pragma once
#include "Vector_Include.h"
template <typename T>
int Vector<T>::remove(Rank left, Rank right)		//O(n-right)
{
	if (left == right)
	{
		return 0;//����Ч�ʿ��ǣ����������˻����
	}
	
	while (right < _size)
	{
		_elem[left++] = _elem[right++];// [right��_size) ˳��ǰ�� right-left λ
	}
	_size = left;//���¹�ģ
	shrink();//���б�Ҫ������

	return right - left;//���ر�ɾ��Ԫ�ص���Ŀ
}

template <typename T> 
T Vector<T>::remove(Rank r) 
{ 
	//ɾ����������Ϊr��Ԫ�أ�0 <= r < size
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}