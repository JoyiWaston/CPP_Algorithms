#pragma once
#include "shift.h"

//迭代版
void shift1(int* A, int n, int k)
{
	int mov = 0;
	for (int s = 0; mov < n; s++)
	{
		mov += shift(A, n, s, k);

		cout << "mov = " << mov << endl;
		for (int j = 0; j < n; j++)
		{
			cout << A[j] << " ";
		}
		cout << endl;
	}
	cout << "操作数为：" << mov << endl;
}