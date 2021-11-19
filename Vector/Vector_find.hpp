#pragma once
#include "Vector_Include.h"

//����������TΪ�� �е� �Ļ������ͣ��������ز����� == �� !=
//����������TΪ�� �Ƚ� �Ļ������ͣ��������ز����� <  �� >

template <typename T>	
Rank Vector<T>::find(T const& e, Rank left, Rank right) const		
//O(right - left) = O(n)   �����ж��Ԫ��ʱ�ɷ��� �������
{
	while ((left < right--) && (e != _elem[right]));	//�������

	return right;//right < left ��ζ��ʧ�ܣ�����right������Ԫ�ص���
}// Excel::match(e, range, type);

// �����㷨Ϊ ��������(input-sensitive)�㷨��������O(1),����O(n)