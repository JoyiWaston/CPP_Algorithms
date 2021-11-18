#pragma once
# include <iostream>

using namespace std;


void swap(int& A, int& B)
{
	int temp = 0;
	temp = A;
	A = B;
	B = temp;
}

//不变性：经过k轮扫描交换后，最大的k个元素必然就位
//单调性：经过k轮扫描交换后，问题规模缩减至n-k
//正确性：经过至多n趟扫描后，算法必然终止，且能给出正确解答
void BubbleSort(int A[], int n)
{
	for (bool sorted = false; sorted = !sorted; n--)
	{
		for (int i = 1; i < n; i++)
		{
			if (A[i - 1] > A[i])
			{
				swap(A[i - 1], A[i]);
				sorted = false;
			}
		}
	}
}
