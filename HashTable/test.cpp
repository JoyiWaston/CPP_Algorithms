#include "HashTable.hpp"

int main()
{
	HashTable<int> h = HashTable<int>(13);

	h.insertHash(66);h.insertHash(32);
	h.insertHash(98);h.insertHash(478);
	h.insertHash(11);h.insertHash(23);
	h.insertHash(43);h.insertHash(55);
	h.insertHash(67);h.insertHash(108);
	h.insertHash(230);h.insertHash(223);
	h.insertHash(10);

	cout << "--------------���ر���--------------" << endl;
	for (int i = 0; i < 13; i++)
	{
		cout << h[i] << " ";
	}
	cout << endl;
	cout << "--------------getElem����--------------" << endl;
	for (int i = 1; i <= 13; i++)
	{
		cout << h.getElem(i) << " ";
	}
	cout << endl;

	cout << "--------------����Ԫ�ص�λ��--------------" << endl;
	int i = 0;
	cin >> i;
	cout << "Ԫ��" << i << "�ڹ�ϣ���е�λ��Ϊ��" << h.searchHash(i) << endl;


	return 0;
}