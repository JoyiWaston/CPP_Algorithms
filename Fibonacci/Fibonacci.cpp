# include <iostream>

using namespace std;

// 动态规划
// Kent Beck : 
// Make it work, make it right,			//递归
// make it fast.						//迭代
// 理解：所谓动态规划，也就是通过 递归 找到了算法的本质，
//       并且给出一个初步的解之后，再将其等效的转化为 迭代 的形式

// fibonacci数
// fib(n) = fib(n-1) + fib(n-2) : {0 , 1 , 1 , 2 , 3 , 5 , 8 ,...}

//计算fibonacci数列的第n项（二分递归版）	// 辣鸡算法
__int64 fib1(int n)
{
	return (2 > n) ? (__int64)n : fib1(n - 1) + fib1(n - 2);		// 若达到递归基，直接取值，否则计算前两项之和即为第n项
}

// T(n) = Φ(n)		Φ = (1+(5^(1/2)))/2      黄金分割比 1.61803........
// Φ^36 = 2^25   Φ^43 = 2^30 = (2^10)^3 = (10^3)^3 = 10^9 flo = 1 sec 
// Φ^5 = 10	  Φ^67 = 10^14 flo = 10^5 sec = 1 day			Φ^92 = 10^19 flo = 10^10 = 10^5 day = 3 century

//解决方案A ： 将已计算过实例的结果制表备查		入口处加查询语句，只有表中没有的结果，才去计算得出
//解决方案B ： 动态规划：颠倒计算方向，由自顶而下递归改为自底而上迭代

//迭代版		O(1) 的空间
__int64 fib2(int n)
{
	__int64 f = 0, g = 1;
	while (0 < n--)
	{
		g = g + f;
		f = g - f;
	}
	return g;
}

int main()
{
	__int64 result = fib2(64);
	cout << result << endl;
}