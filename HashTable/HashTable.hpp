#pragma once
#include <iostream>

using namespace std;

template<class T>
class HashTable
{
public:
	HashTable(int size)
	{
		maxSize = size;//初始化最大存储空间
		count = 0;
		elem = new T[size];//分配数据空间
		if (elem == nullptr) { exit(1); }//判断空间是否分配成功
		for (int i = 0; i < size; i++) { elem[i] = NULL; }
	}
	~HashTable()
	{
		delete[] elem;
	}

	//散列（哈希）函数——除留取余，p为根据关键字集合设定的值
	int hash(T const& e/*, int p*/);
	//查找函数，返回所查找元素的地址
	int searchHash(T const& e);
	//获取散列表的第i个元素的值
	T getElem(int i);
	//插入元素到散列表
	bool insertHash(T const& e);

	//重载[]
	T& operator[](int r) { return elem[r]; }


private:
	int maxSize;//最大容量
	int count;//当前元素数
	T* elem;//数据域
};

//hash函数
template<typename T>
int HashTable<T>::hash(T const& e/*, int p*/)
{
	int p = 13;//p取小于或等于表长（尽量接近表长）的最小素数
	return e % p;//采用除留取余法计算散列地址
}

//查找算法
template<typename T>
int HashTable<T>::searchHash(T const& e)
{
	int p = hash(e);//计算地址
	if (elem[p] == e) { return p; }//计算地址，如果相等，且没有发生冲突，则返回p

	int rp = (p + 1) % maxSize;//线性探测法处理冲突，选取d=1
	while (rp != p)
	{
		if (elem[rp] == e) { return rp; }//如果新地址的值与e相等，则返回新地址
		if (elem[rp] == NULL) { break; }//找到空白地址
		rp = (rp + 1) % maxSize;//循环使用线性探测法寻找空白地址
	}
	if (rp == p) { return -2; }//查找失败
	else
	{
		elem[rp] = e;//在空白地址插入此元素并返回地址
		return rp;
	}
}

//获取散列表的第i个元素的值
template<typename T>
T HashTable<T>::getElem(int i)
{
	if (i < 0) { cout << "索引值错误！必须为正整数！" << endl; }
	return elem[i - 1];
}

//插入元素到散列表
template<typename T>
bool HashTable<T>::insertHash(T const& e)
{
	int pos = searchHash(e);//查找待插入元素，看看散列表中是否已存在该元素
	if (pos < 0) { return false; }//查找失败且表满
	else if (elem[pos] == e) { cout << "重复元素！" << endl; return false; }//有与哈希表中重复的元素
	else { elem[pos] = e; return true; }//在空白地址插入元素
}