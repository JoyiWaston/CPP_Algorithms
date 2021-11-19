#pragma once
#include "shift.h"

//void swap(int& A, int& B)
//{
//	int temp = 0;
//	temp = A;
//	A = B;
//	B = temp;
//}

void for_each(int* A,int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

void reverse(int* A, int left, int right)
{
	if (left < right)
	{
		swap(A[left], A[right]);
		reverse(A, left + 1, right - 1);
	}
}

void reverse(int* A, int n)
{
	reverse(A, 0, n - 1);
}

void shift2(int* A, int n, int k)
{
	k %= n; //确保k <= n

	for_each(A, n);

	reverse(A, k);				//O(3k/2)
	reverse(A + k, n - k);		//O(3(n-k)/2)
	reverse(A, n);				//O(3n/2)

	for_each(A, n);

	cout << "操作数为：" << 3*n << endl;
}

//缓存机制
//shift2比shift1快的多，cache缓存访问比shift1效率的多，shift1数据之间是混沌的;
//原因涉及操作系统（分页）