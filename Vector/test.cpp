# include "Vector.hpp"

int main()
{
	int A[] = { 3,1,2,4,1,2,3,4,5,6,7,8,9 };

	Vector<int> v(A,sizeof(A)/sizeof(int));

	/*v.insert(24);
	v.insert(0, 30);*/
	
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	/*cout << "6�ڣ�" << v.find(6) << endl;
	v.remove(1);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;*/

	//cout << "���������У�" << v.disordered() << " ������ԣ�" << endl;

	/*v.deduplicate();
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "10 �����������ģ�" << v.search(10) << " λ��" << endl;*/

	v.sort();
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}