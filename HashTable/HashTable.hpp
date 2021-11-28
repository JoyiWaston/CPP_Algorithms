#pragma once
#include <iostream>

using namespace std;

template<class T>
class HashTable
{
public:
	HashTable(int size)
	{
		maxSize = size;//��ʼ�����洢�ռ�
		count = 0;
		elem = new T[size];//�������ݿռ�
		if (elem == nullptr) { exit(1); }//�жϿռ��Ƿ����ɹ�
		for (int i = 0; i < size; i++) { elem[i] = NULL; }
	}
	~HashTable()
	{
		delete[] elem;
	}

	//ɢ�У���ϣ��������������ȡ�࣬pΪ���ݹؼ��ּ����趨��ֵ
	int hash(T const& e/*, int p*/);
	//���Һ���������������Ԫ�صĵ�ַ
	int searchHash(T const& e);
	//��ȡɢ�б�ĵ�i��Ԫ�ص�ֵ
	T getElem(int i);
	//����Ԫ�ص�ɢ�б�
	bool insertHash(T const& e);

	//����[]
	T& operator[](int r) { return elem[r]; }


private:
	int maxSize;//�������
	int count;//��ǰԪ����
	T* elem;//������
};

//hash����
template<typename T>
int HashTable<T>::hash(T const& e/*, int p*/)
{
	int p = 13;//pȡС�ڻ���ڱ��������ӽ���������С����
	return e % p;//���ó���ȡ�෨����ɢ�е�ַ
}

//�����㷨
template<typename T>
int HashTable<T>::searchHash(T const& e)
{
	int p = hash(e);//�����ַ
	if (elem[p] == e) { return p; }//�����ַ�������ȣ���û�з�����ͻ���򷵻�p

	int rp = (p + 1) % maxSize;//����̽�ⷨ�����ͻ��ѡȡd=1
	while (rp != p)
	{
		if (elem[rp] == e) { return rp; }//����µ�ַ��ֵ��e��ȣ��򷵻��µ�ַ
		if (elem[rp] == NULL) { break; }//�ҵ��հ׵�ַ
		rp = (rp + 1) % maxSize;//ѭ��ʹ������̽�ⷨѰ�ҿհ׵�ַ
	}
	if (rp == p) { return -2; }//����ʧ��
	else
	{
		elem[rp] = e;//�ڿհ׵�ַ�����Ԫ�ز����ص�ַ
		return rp;
	}
}

//��ȡɢ�б�ĵ�i��Ԫ�ص�ֵ
template<typename T>
T HashTable<T>::getElem(int i)
{
	if (i < 0) { cout << "����ֵ���󣡱���Ϊ��������" << endl; }
	return elem[i - 1];
}

//����Ԫ�ص�ɢ�б�
template<typename T>
bool HashTable<T>::insertHash(T const& e)
{
	int pos = searchHash(e);//���Ҵ�����Ԫ�أ�����ɢ�б����Ƿ��Ѵ��ڸ�Ԫ��
	if (pos < 0) { return false; }//����ʧ���ұ���
	else if (elem[pos] == e) { cout << "�ظ�Ԫ�أ�" << endl; return false; }//�����ϣ�����ظ���Ԫ��
	else { elem[pos] = e; return true; }//�ڿհ׵�ַ����Ԫ��
}