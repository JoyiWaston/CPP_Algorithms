// 02_Copy_constructor.h: 目标的头文件。
//双向链表类

#pragma once
# include <iostream>

using namespace std;

template <class T>
class DoublyLinkList
{
	//template <class U>
	//friend class myLinkNode<U>;
	//存储结点类
	template <class T>
	class myLinkNode
	{
		friend class DoublyLinkList;		//将链式表声明为友类

	public:
		myLinkNode()	//构造函数
		{
			next = nullptr;
			previous = nullptr;
		}
		myLinkNode(const T item, myLinkNode<T>* previous, myLinkNode<T>* next)
		{
			data = item;
			next = nullptr;
			previous = nullptr;
		}
		~myLinkNode()
		{
			next = nullptr;
			previous = nullptr;
		}

	private:
		T data;						//结点元素
		myLinkNode<T>* next;			//指向下一个结点的指针
		myLinkNode<T>* previous;		//指向上一个结点 的指针
	};


public:
	DoublyLinkList();	//构造
	~DoublyLinkList();	//析构
	DoublyLinkList<T>& Insert(int k, const T& x);
	bool IsEmpty() const;
	int GetLength() const;
	bool GetData(int k, T& x);
	bool ModifyData(int k, const T& x);
	int Find(const T& x);
	DoublyLinkList<T>& DeleteByIndex(int k, T& x);
	DoublyLinkList<T>& DeleteByKey(const T& x, T& y);
	void OutPut(ostream& out);


private:
	myLinkNode<T>* head;	//指向链表的第一个头结点的指针
};

//构造（创建空单向链表）
template <class T>
DoublyLinkList<T>::DoublyLinkList()
{
	head = new myLinkNode<T>();//创建头结点
}

//插入算法实现
//对于插入元素的操作Insert，假设当前表中已有n个元素，当在第k个位置之前插入结点new Node时，需要分四种情况处理：
template <class T>
DoublyLinkList<T>& DoublyLinkList<T>::Insert(int k, const T& x)
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

		if (p->next != nullptr)//判断是否在双向链表尾部添加结点
		{
			p->next->previous = newNode;
		}
		newNode->previous = p;
		p->next = newNode;
	}
	return *this;
}

//删除算法实现
template <class T>
DoublyLinkList<T>& DoublyLinkList<T>::DeleteByIndex(int k, T& x)
{
	//2、当k=1时，只需要将头结点的指针域指向第二个结点，然后释放第k个结点即可
	//3、当1<k<n时，只需要将第k-1个元素结点的next指针指向第k+1个元素结点，然后释放第k个结点即可
	//4、当k=n时，将第n-1个元素结点的next指针赋值为nullptr，然后释放第k个结点即可
	if (GetData(k, x))
	{
		myLinkNode<T>* p = head->next;//p指向头结点
		myLinkNode<T>* q = nullptr;//q指向空地址
		
		for (int i = 1; i < k; i++)
		{
			p = p->next;//将p指针移动到第k-1个结点
			if (p == nullptr)
			{
				cout << "超出链表范围！" << endl;
			}
		}
		if (k == GetLength())
		{
			p->previous->next = nullptr;
			delete q;//物理删除该结点
		}
		else
		{
			q = p;//q指向待删除的第k个结点
			p->previous->next = q->next;//待 删结点的前结点的next指针指向待删结点后一个结点
			p->next->previous = q->previous;//待删结点的下一个结点的previous指针指向待删结点的前一个结点
			delete q;//物理删除该结点
		}
		
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
DoublyLinkList<T>& DoublyLinkList<T>::DeleteByKey(const T& x, T& y)
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
bool DoublyLinkList<T>::IsEmpty() const
{
	return head->next == nullptr;
}

//求当前表长度算法实现
template <class T>
int DoublyLinkList<T>::GetLength() const
{
	int length = 0;
	myLinkNode<T>* p = head->next;
	while (p!=nullptr)
	{
		length++;
		p = p->next;
	}
	return length;
}

//按位置取元素算法实现
template <class T>
bool DoublyLinkList<T>::GetData(int k, T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;
	if (k<1 || k>GetLength())
	{
		return false;
	}
	while (p != nullptr && index < k)
	{
		index++;
		p = p->next;
	}
	if (p == nullptr)
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
bool DoublyLinkList<T>::ModifyData(int k, const T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;

	if (k<1 || k>GetLength())
	{
		return false;
	}
	while (p != nullptr && index < k)
	{
		index++;
		p = p->next;
	}
	if (p == nullptr)
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
int DoublyLinkList<T>::Find(const T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;
	while (p != nullptr && p->data != x)
	{
		p = p->next;
		index++;
	}
	if (p != nullptr)
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
void DoublyLinkList<T>::OutPut(ostream& out)
{
	myLinkNode<T>* p = head->next;

	while (p != nullptr)
	{
		out << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//重载运算符<<
template<class T>
ostream& operator<<(ostream& out, DoublyLinkList<T>& x)
{
	x.OutPut(out);
	return out;
}


//析构（清空单向链表）
template <class T>
DoublyLinkList<T>::~DoublyLinkList()
{
	myLinkNode<T>* p = head->next;
	myLinkNode<T>* q = nullptr;

	while (p != nullptr)
	{
		q = p;
		p = q->next;
		delete q;
	}
	head->next = nullptr;

	delete head;
}