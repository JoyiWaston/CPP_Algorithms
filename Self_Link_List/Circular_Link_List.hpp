#pragma once
# include <iostream>

using namespace std;

template <class T>
class CircularLinkList
{
	//template <class U>
	//friend class myLinkNode<U>;
	//存储结点类
	template <class T>
	class myLinkNode
	{
		friend class CircularLinkList;		//将链式表声明为友类

	public:
		myLinkNode()	//构造函数
		{
			next = nullptr;
		}

	private:
		T data;						//结点元素
		myLinkNode<T>* next;			//指向下一个结点的指针
	};


public:
	CircularLinkList();	//构造
	~CircularLinkList();	//析构
	CircularLinkList<T>& Insert(int k, const T& x);
	bool IsEmpty() const;
	int GetLength() const;
	bool GetData(int k, T& x);
	bool ModifyData(int k, const T& x);
	int Find(const T& x);
	CircularLinkList<T>& DeleteByIndex(int k, T& x);
	CircularLinkList<T>& DeleteByKey(const T& x, T& y);
	void OutPut(ostream& out);


private:
	myLinkNode<T>* head;	//指向链表的第一个头结点的指针
};

//构造（创建循环链表）
template <class T>
CircularLinkList<T>::CircularLinkList()
{
	head = new myLinkNode<T>();//创建头结点
	head->next = head;
}

//插入算法实现
//对于插入元素的操作Insert，假设当前表中已有n个元素，当在第k个位置之前插入结点new Node时，需要分四种情况处理：
template <class T>
CircularLinkList<T>& CircularLinkList<T>::Insert(int k, const T& x)
{
	myLinkNode<T>* p = head;//p指向头结点
	myLinkNode<T>* newNode = new myLinkNode<T>;//创建待插入的新结点

	newNode->data = x;
	int len = GetLength();

	//1、当k>n+1或k<1时，插入位置不正确，报错
	if (k<1 || k>len + 1)
	{
		cout << "插入位置不正确，插入失败！" << endl;
	}
	//2、当是空白表且k=1时，只需要将head->next指向新结点即可
	//3、当不是空表且k=1时，需要将新结点的next指针指向第1个元素结点，再将头结点的指针域指向new Node结点即可
	//4、当1<k<=n时，将new Node的next指针指向第k个元素结点，将第k-1个元素结点的next指针指向new Node即可
	else
	{
		for (int i = 1; i < k; i++)
		{
			p = p->next;	//将p移动到第k-1个结点
		}
		newNode->next = p->next;//在k处插入新结点
		p->next = newNode;
	}

	return *this;
}

//删除算法实现
template <class T>
CircularLinkList<T>& CircularLinkList<T>::DeleteByIndex(int k, T& x)
{
	//2、当k=1时，只需要将头结点的指针域指向第二个结点，然后释放第k个结点即可
	//3、当1<k<n时，只需要将第k-1个元素结点的next指针指向第k+1个元素结点，然后释放第k个结点即可
	//4、当k=n时，将第n-1个元素结点的next指针赋值为nullptr，然后释放第k个结点即可
	if (GetData(k, x))
	{
		myLinkNode<T>* p = head;//p指向头结点
		myLinkNode<T>* q = nullptr;//q指向空地址
		for (int i = 1; i < k; i++)
		{
			p = p->next;//将p指针移动到第k-1个结点
		}
		q = p->next;//q指向待删除的第k个结点
		p->next = q->next;//将第k个结点从链表中移除
		delete q;//物理删除该结点
	}

	//1、当k>n或k<1时，删除位置不正确，报错
	else
	{
		cout << "删除位置不正确，删除失败！" << endl;
	}

	return *this;
}

//按关键字删除算法实现
template <class T>
CircularLinkList<T>& CircularLinkList<T>::DeleteByKey(const T& x, T& y)
{
	int index = Find(x);//得到要删除的元素位置

	if (index != 0)
	{
		return DeleteByIndex(index, y);
	}
	else
	{
		cout << "链表内没有该元素，删除失败！" << endl;
		return *this;
	}
}

//判断空表算法实现
template<class T>
bool CircularLinkList<T>::IsEmpty() const
{
	return head->next == head;
}

//求当前表长度算法实现
template <class T>
int CircularLinkList<T>::GetLength() const
{
	int length = 0;
	myLinkNode<T>* p = head->next;
	while (p!=head)
	{
		length++;
		p = p->next;
	}
	return length;
}

//按位置取元素算法实现
template <class T>
bool CircularLinkList<T>::GetData(int k, T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;
	if (k<1 || k>GetLength())
	{
		return false;
	}
	while (p != head && index < k)
	{
		index++;
		p = p->next;
	}
	if (p == head)
	{
		return false;
	}
	else
	{
		x = p->data;
		return true;
	}
}

//按位置修改元素算法实现
template<class T>
bool CircularLinkList<T>::ModifyData(int k, const T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;

	if (k<1 || k>GetLength())
	{
		return false;
	}
	while (p != head && index < k)
	{
		index++;
		p = p->next;
	}
	if (p == head)
	{
		return false;
	}
	else
	{
		p->data = x;
		return true;
	}
}

//按关键字查找算法实现
template<class T>
int CircularLinkList<T>::Find(const T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;
	while (p != head && p->data != x)
	{
		p = p->next;
		index++;
	}
	if (p != head)
	{
		return index;
	}
	else
	{
		return 0;
	}
}

//实现链表打印算法
template<class T>
void CircularLinkList<T>::OutPut(ostream& out)
{
	myLinkNode<T>* p = head->next;

	while (p != head)
	{
		out << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//重载运算符<<
template<class T>
ostream& operator<<(ostream& out, CircularLinkList<T>& x)
{
	x.OutPut(out);
	return out;
}

//析构（清空循环链表）
template <class T>
CircularLinkList<T>::~CircularLinkList()
{
	myLinkNode<T>* p;
	while (head->next != head)
	{
		p = head->next;
		head->next = p->next;
		delete p;
	}
	delete head;//释放头结点
}