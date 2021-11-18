﻿// 减而治之 Decrease-and-conquer

#pragma once
#include <iostream>
using namespace std;



// 为求解一个大规模问题，可以：
// 将其划分为两个子问题：其一平凡（退化的），另一规模			// 单调性
// 分别求解子问题
// 由子问题的解，得到原问题的解

int SumA1(int A[], int n)				// n为问题规模
{
	int sum = 0;						// O(1)
	for (int i = 0; i < n; i++)			// O(n)
	{				
		sum += A[i];					// O(1)			// 不断削减问题规模
	}
	return sum;							// O(1)
}
// 无论A[]内容为何，T(n) = 1 + n * 1 +1 = n + 2 = O(n) = Ω(n) = Θ(n)
// 空间复杂度：O(2)

// 改良：线性递归
int SumA2(int A[], int n)
{
	return (n < 1) ? 0 : SumA2(A, n - 1) + A[n - 1];
}
// 1、递归跟踪分析：
// 特点：直观形象，仅适用于简明的递归模式
// 检测每个递归实例 累计所需时间（调用语句本身，计入对应的子实例） 其总和为算法执行时间

// 2、递推方程分析：(求微分方程)
// 从递推的角度看，为求解 SumI2(A,n) ，需要递归求解规模为 n-1 的问题 SumI2(A,n-1)  // T(n-1)
// 再累加上 A[n-1]  (平凡)																   // O(1)
// 递归基：SumI2(A,0)
// 递推方程：T(n) = T(n-1) + O(1)    递推基：T(0) = O(1)
// 求解：
// T(n) - n = T(n-1) - (n-1) = T(n-2) - (n-2) = ...
//			= T(2) - 2
//			= T(1) - 1
//			= T(0)
// T(n)     = O(1) + n = O(n)

// 本例中，单个递归实例自身只需要O(1)的时间复杂度
// T(n) = O(1) * (n+1) = O(n)


// 分而治之：   Divide-and-conquer
// 为求解一个大规模的问题，可以
// 将其划分为若干（通常为两个）子问题，规模大体相当
// 分别求解子问题
// 由子问题得到原问题的解

//数组求和：二分递归

//入口形式为 SumA3(A,0,n-1)
int SumA3(int A[], int lo, int hi)
{
	//区间范围A[lo,hi]
	if (lo == hi)
	{
		return A[lo];	//递归基
	}
	int mi = (lo + hi) >> 1;		// >> 1 相当于除二
	
	return SumA3(A, lo, mi) + SumA3(A, mi + 1, hi);
}

// T(n) = 各层递归实例所需时间的和
//		= O(1) * (2^0 + 2^1 + 2^2 + ... + 2^logn)			//几何级数的综合和 末项的阶数（2^logn） 同阶
//		= O(1) * (2^log(n+1) - 1) 
//		= O(n)