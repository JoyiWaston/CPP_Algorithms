#include "List.hpp"

int main()
{
	List<int> L1;
	L1.insertAsFirst(100);
	L1.insertAsLast(20);
	L1.insertAsFirst(200);
	L1.insertAsLast(40);



	for (int i = 0; i < L1.size(); i++)
	{
		cout << L1[i] << " ";
	}
	cout << endl;

	L1.sort();
	for (int i = 0; i < L1.size(); i++)
	{
		cout << L1[i] << " ";
	}
	cout << endl;

}