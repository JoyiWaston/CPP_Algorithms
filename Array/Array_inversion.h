// ������֮ Decrease-and-conquer

#pragma once
# include <iostream>
using namespace std;

// ���鵹��
// �θ�����A[0,n],����ǰ��ߵ�
// ͳһ�ӿڣ�void reverse(int* A, int lo, int hi)

void swap(int& A, int& B)
{
	int temp = 0;
	temp = A;
	A = B;
	B = temp;
}

//�ݹ��
void RecursionReverse(int* A, int lo, int hi)
{
	if (lo < hi)	//�����ģ�� ��ż�� ���䣬��Ҫ�����ݹ��
	{
		swap(A[lo] < A[hi]);			// O(1)
		RecursionReverse(A, lo + 1, hi - 1);
	}
	//���� else return //�ݹ��
}

// ----------------------n----------------------
// lo------------------(n-2)------------------hi


//������
void IterationReverse(int* A, int lo, int hi)
{
	next:
		if (lo < hi)
		{
			swap(A[lo], A[hi]);
			lo++;
			hi--;
			goto next;
		}
}

//���������
void EasyIterationReverse(int* A, int lo, int hi)
{
	while (lo < hi)
	{
		swap(A[lo++], A[hi--]);
	}
}