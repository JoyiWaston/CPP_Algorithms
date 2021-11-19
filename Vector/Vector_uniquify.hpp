#pragma once
#include "Vector_Include.h"


//��Ч�㷨		O(n^2)
//ԭ�򣺵�Ч�ĸ�Դ���ڣ�ͬһԪ�ؿ���Ϊ��ɾ��Ԫ�صĺ�̶��ǰ��
//��ʾ���������ظ�����Ϊ��λ������ɾ����ͬԪ�أ����ܱؽ��Ľ�
//template<typename T>
//int Vector<T>::uniquify()
//{
//	int oldSize = _size;
//	int i = 0;					//����Ԫ�ؿ�ʼ
//
//	while (i < _size - 1)		//��ǰ�����һ�ȶԸ�������Ԫ�أ���ͬ��ɾ�����ߣ�����ת����һ��Ԫ��
//	{
//		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;
//	}
//	return oldSize = _size;//������ģ�仯������ɾ��Ԫ������
//}//ע�⣺����_size�ļ�С����remove()��ʽ�����

//��Ч��
template<typename T>
int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;//���Ի���"����"Ԫ�ص���
	while (++j < _size)//��һɨ�裬ֱ��ĩԪ��
	//������ͬ�ߣ����ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();//ֱ�ӽس�β������Ԫ��

	return j - i;//������ģ�仯��������ɾ��Ԫ������
}//ע�⣺ͨ��remove(left,right)����ɾ������Ȼ���ܴﵽ��Ч��