#include "Bubble_Sort.h"

//BubbleSort
void test01()
{
	int A[] = { 5,4,6,25,324,21,3,4,6345,7,534,1,3,5,634,63,12,34,124 };
	//cout << sizeof(A)/sizeof(int) << endl;
	BubbleSort(A, sizeof(A) / sizeof(int));

	for (int i = 0; i < sizeof(A) / sizeof(int); i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

int main()
{
	test01();

	return 0;
}
