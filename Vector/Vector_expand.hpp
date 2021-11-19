#pragma once
#include "Vector_Include.h"

template <typename T>
void Vector<T>::expand()//�����ռ䲻��ʱ����
{
	if (_size < _capacity)
	{
		return;
	}

	_capacity = max(_capacity, DEFAULT_CAPACITY);//��������С����

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//�����ӱ�		���μ���O��n����		�̶���ֵ����	��������O(n^2) ;
	for (int i = 0; i < _size; i++)//����ԭ��������
	{
		_elem[i] = oldElem[i];	   //TΪ�������ͣ��������ظ�ֵ������'='
	}

	delete[] oldElem;//�ͷ�ԭ�ռ�
}