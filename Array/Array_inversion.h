// 减而治之 Decrease-and-conquer

#pragma once
# include <iostream>
using namespace std;

// 数组倒置
// 任给数组A[0,n],将其前后颠倒
// 统一接口：void reverse(int* A, int lo, int hi)

void swap(int& A, int& B)
{
	int temp = 0;
	temp = A;
	A = B;
	B = temp;
}

//递归版
void RecursionReverse(int* A, int lo, int hi)
{
	if (lo < hi)	//问题规模的 奇偶性 不变，需要两个递归基
	{
		swap(A[lo] < A[hi]);			// O(1)
		RecursionReverse(A, lo + 1, hi - 1);
	}
	//隐含 else return //递归基
}

// ----------------------n----------------------
// lo------------------(n-2)------------------hi


//迭代版
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

//迭代精简版
void EasyIterationReverse(int* A, int lo, int hi)
{
	while (lo < hi)
	{
		swap(A[lo++], A[hi--]);
	}
}