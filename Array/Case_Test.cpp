#include "Array_Sum.h"
#include "Array_inversion.h"

int main()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int s = sizeof(A) / sizeof(int);
	cout << s << endl;

	cout << "A1方法数组求和：" << SumA1(A, s) << endl;
	cout << "A2方法数组求和：" << SumA2(A, s) << endl;
	cout << "A3方法数组求和：" << SumA3(A, 0, s - 1) << endl;

	RecursionReverse(A, 0, s - 1);
	cout << "经过递归转置后的数组为：" << endl;
	for (int i = 0; i < s; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;

	IterationReverse(A, 0, s - 1);
	cout << "经过迭代转置后的数组为：" << endl;
	for (int i = 0; i < s; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;

	EasyIterationReverse(A, 0, s - 1);
	cout << "经过精简迭代转置后的数组为：" << endl;
	for (int i = 0; i < s; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}