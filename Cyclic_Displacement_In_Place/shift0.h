#pragma once
#include "shift.h"


//�����㷨
void shift0(int* A, int n, int k)
{
	int mov = 0;
	while (k--)
	{
		mov += shift(A, n, 0, 1);

		cout << "mov = " << mov << endl;
		for (int j = 0; j < n; j++)
		{
			cout << A[j] << " ";
		}
		cout << endl;
	}
	cout << "������Ϊ��" << mov << endl;
}