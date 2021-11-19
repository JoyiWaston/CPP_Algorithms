#pragma once
#include "Vector_Include.h"

//���ú���ָ����ƣ�ֻ���� �ֲ��� �޸�
template <typename T>
void Vector<T>::traverse(void (*visit)(T&))//����ָ��
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//���ú���������ƣ��� ȫ�����޸�
template <typename T>	template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}