#pragma once
#include "Vector_Include.h"

//Ψһ�����㷨
//Ӧ��ʵ������������ �ľֲ��������ȥ�ز���������Ϊ���ձ���

// ������
//template <typename T>
//int Vector<T>::deduplicate()
//{
//	int oldSize = _size;//��¼ԭ��ģ
//	Rank i = 1;//��_elem[1]��ʼ
//
//	while (i < _size)//��ǰ���ע�⿼���Ԫ��_elem[i]
//	{
//		//��ǰ׺��Ѱ����ͬ��
//		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);//������ͬ�����������
//		//����ɾ����ͬ(����ֻ��һ����ֵͬ��)
//	}
//	return oldSize - _size;//������ģ�仯�ˣ���ɾ��Ԫ������
//}

//ɾ�������������ظ�Ԫ�أ���Ч�棩
template <typename T> 
int Vector<T>::deduplicate() 
{ 
    
    int oldSize = _size; //��¼ԭ��ģ
    Rank i = 1; //��_elem[1]��ʼ

    while (i < _size) //��ǰ�����һ�����Ԫ��_elem[i]
    {
        if (find(_elem[i], 0, i) < 0) //��ǰ׺[0,i)��Ѱ����֮��ͬ�ߣ�����һ����
        {
            i++; //������ͬ�������������
        }
        else
        {
            remove(i); //����ɾ����ǰԪ��
        }
    }
    return oldSize - _size; //��ɾ��Ԫ������
}