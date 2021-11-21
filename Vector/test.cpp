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

	/*cout << "6在：" << v.find(6) << endl;
	v.remove(1);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;*/

	//cout << "该向量中有：" << v.disordered() << " 个逆序对！" << endl;

	/*v.deduplicate();
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "10 在有序向量的：" << v.search(10) << " 位！" << endl;*/

	v.sort();
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}