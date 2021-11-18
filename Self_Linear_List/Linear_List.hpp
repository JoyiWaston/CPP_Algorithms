//线性表实现
#pragma once

#include <iostream>

using namespace std;
// TODO: 在此处引用程序需要的其他标头。

template <class T>
class LinearList
{
public:
	LinearList(int LLMaxSize);	//构造函数，创建空表
	~LinearList();				//析构函数，删除表

	LinearList<T>& Insert(int k, const T& x);	//在第k个位置插入元素x，返回插入后的线性表

	bool IsEmpty() const;		//判断表是否为空，空返回true

	int GetLength() const;		//返回表中数据个数

	bool GetData(int k, T& x);	//将表中第k个元素保存到x中，不存在则返回false

	bool ModifyData(int k, const T& x);//将表中第k个元素修改为x，不存在则返回false

	int Find(const T& x);		//返回x在表中的位置，如果x不在表中返回0

	LinearList<T>& DeleteByIndex(int k, T& x);//删除表中第k个元素，并把它保存到x中，返回删除后的线性表

	LinearList<T>& DeleteByKey(const T& x, T& y);//删除表中关键字为x的元素，返回删除后的线性表

	void OutPut(ostream& out) const;//将线性表放到输出流out中输出

private:
	int length;					//当前数组元素个数
	int MaxSize;				//线性表中最大元素个数
	T* element;					//一维动态数组
};


//构造函数，创建表
template <class T>
LinearList<T>::LinearList(int LLMaxSize)
{
	this->MaxSize = LLMaxSize;
	this->element = new T[LLMaxSize];
	this->length = 0;
}

//在第k个位置插入元素x，返回插入后的线性表
template <class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
	if (k<1 || k>length + 1)
	{
		cout << "元素下标越界，添加元素失败！" << endl;
	}

	else if (length == MaxSize)
	{
		cout << "该表已满，无法添加新元素！" << endl;
	}

	else
	{
		for (int i = length; i > k - 1; i--)
		{
			element[i] = element[i - 1];
		}
		element[k - 1] = x;
		length++;
	}
	return *this;
}

//判断表是否为空，空返回true
template <class T>
bool LinearList<T>::IsEmpty() const
{
	return length == 0;
}

//实现求当前表长度
template <class T>
int LinearList<T>::GetLength() const
{
	return length;
}

//实现按位置取元素
template<class T>
bool LinearList<T>::GetData(int k, T& x)
{
	if (k<1 || k>length)
	{
		return false;
	}
	else
	{
		x = element[k - 1];
		return true;
	}
}

//实现按位置修改元素
template<class T>
bool LinearList<T>::ModifyData(int k, const T& x)
{
	if (k<1 || k>length)
	{
		return false;
	}
	else
	{
		element[k - 1] = x;
		return true;
	}
}

//实现按关键字查找
template<class T>
int LinearList<T>::Find(const T& x)
{
	for (int i = 0; i < length; i++)
	{
		if (element[i] == x)
		{
			return i + 1;
		}
	}
	return 0;
}

//实现按位置删除
template<class T>
LinearList<T>& LinearList<T>::DeleteByIndex(int k, T& x)
{
	if (GetData(k, x))
	{
		for (int i = k - 1; i < length - 1; i++)
		{
			element[i] = element[i + 1];
		}
		length--;
	}
	else
	{
		cout << "元素下标越界，删除失败";
	}
	return *this;
}

//实现按关键字删除
template<class T>
LinearList<T>& LinearList<T>::DeleteByKey(const T& x, T& y)
{
	int index = Find(x);//得到要删除元素的位置
	if (index != 0)
	{
		return DeleteByIndex(index, y);
	}
	else
	{
		cout << "没有此元素，删除失败";
		return *this;
	}
}

//实现顺序表的输出
template<class T>
void LinearList<T>::OutPut(ostream& out) const
{
	for (int i = 0; i < length; i++)
	{
		out << element[i] << " ";
	}
	cout << endl;
}
//重载运算符<<
template<class T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
{
	x.OutPut(out);
	return out;
}

//析构函数，删除表
template <class T>
LinearList<T>::~LinearList()
{
	delete[] this->element;
}
