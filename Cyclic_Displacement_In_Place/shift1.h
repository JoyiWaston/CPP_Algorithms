#pragma once
#include "shift.h"

//������
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
	cout << "������Ϊ��" << mov << endl;
}