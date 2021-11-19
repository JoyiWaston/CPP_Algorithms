# include "shift0.h"
# include "shift1.h"
# include "shift2.h"
void test01()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A) / sizeof(int);
	int k = 3;//原位循环左移k位

	shift0(A, n, k);
}

void test02()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A) / sizeof(int);
	int k = 3;//原位循环左移k位

	shift1(A, n, k);
}

void test03()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A)/sizeof(int);
	int k = 3;//原位循环左移k位

	shift2(A, n, k);
}

int main()
{

	cout << "----------依次位移算法----------" << endl;
	test01();

	cout << "----------直接位移算法----------" << endl;
	test02();

	cout << "----------直接翻转算法----------" << endl;
	test03();

	return 0;
}