#pragma once
#include <iostream>

using namespace std;
//λ��
//A����ָ�룬n���鳤�ȣ�s��ʼԪ�أ�kλ�Ʋ���                                                                     
int shift(int* A, int n, int s, int k)
{
	//��A[s]��������kΪ���ѭ�����ƣ�O(n / GCD(n, k))
	int bak = A[s]; //������ʼԪ��
	int i = s, j = (s + k) % n; //�Ӹ�Ԫ�س���
	int mov = 0; //�ƶ�����

	while (s != j)
	{
		//��kΪ���
		A[i] = A[j]; //��������kλ
		i = j; j = (j + k) % n; mov++;
	}

	A[i] = bak; //����ʼԪ��ת���Ӧλ��
	return mov + 1;
}