# include "shift0.h"
# include "shift1.h"
# include "shift2.h"
void test01()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A) / sizeof(int);
	int k = 3;//ԭλѭ������kλ

	shift0(A, n, k);
}

void test02()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A) / sizeof(int);
	int k = 3;//ԭλѭ������kλ

	shift1(A, n, k);
}

void test03()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(A)/sizeof(int);
	int k = 3;//ԭλѭ������kλ

	shift2(A, n, k);
}

int main()
{

	cout << "----------����λ���㷨----------" << endl;
	test01();

	cout << "----------ֱ��λ���㷨----------" << endl;
	test02();

	cout << "----------ֱ�ӷ�ת�㷨----------" << endl;
	test03();

	return 0;
}