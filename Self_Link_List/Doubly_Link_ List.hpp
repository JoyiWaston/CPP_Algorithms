// 02_Copy_constructor.h: Ŀ���ͷ�ļ���
//˫��������

#pragma once
# include <iostream>

using namespace std;

template <class T>
class DoublyLinkList
{
	//template <class U>
	//friend class myLinkNode<U>;
	//�洢�����
	template <class T>
	class myLinkNode
	{
		friend class DoublyLinkList;		//����ʽ������Ϊ����

	public:
		myLinkNode()	//���캯��
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
		T data;						//���Ԫ��
		myLinkNode<T>* next;			//ָ����һ������ָ��
		myLinkNode<T>* previous;		//ָ����һ����� ��ָ��
	};


public:
	DoublyLinkList();	//����
	~DoublyLinkList();	//����
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
	myLinkNode<T>* head;	//ָ������ĵ�һ��ͷ����ָ��
};

//���죨�����յ�������
template <class T>
DoublyLinkList<T>::DoublyLinkList()
{
	head = new myLinkNode<T>();//����ͷ���
}

//�����㷨ʵ��
//���ڲ���Ԫ�صĲ���Insert�����赱ǰ��������n��Ԫ�أ����ڵ�k��λ��֮ǰ������new Nodeʱ����Ҫ�������������
template <class T>
DoublyLinkList<T>& DoublyLinkList<T>::Insert(int k, const T& x)
{
	myLinkNode<T>* p = head;//pָ��ͷ���
	myLinkNode<T>* newNode = new myLinkNode<T>;//������������½��

	newNode->data = x;
	int len = GetLength();

	//1����k>n+1��k<1ʱ������λ�ò���ȷ������
	if (k<1 || k>len + 1)
	{
		cout << "����λ�ò���ȷ������ʧ�ܣ�" << endl;
	}
	//2�����ǿհױ���k=1ʱ��ֻ��Ҫ��head->nextָ���½�㼴��
	//3�������ǿձ���k=1ʱ����Ҫ���½���nextָ��ָ���1��Ԫ�ؽ�㣬�ٽ�ͷ����ָ����ָ��new Node��㼴��
	//4����1<k<=nʱ����new Node��nextָ��ָ���k��Ԫ�ؽ�㣬����k-1��Ԫ�ؽ���nextָ��ָ��new Node����
	else
	{
		for (int i = 1; i < k; i++)
		{
			p = p->next;	//��p�ƶ�����k-1�����
		}
		newNode->next = p->next;//��k�������½��

		if (p->next != nullptr)//�ж��Ƿ���˫������β����ӽ��
		{
			p->next->previous = newNode;
		}
		newNode->previous = p;
		p->next = newNode;
	}
	return *this;
}

//ɾ���㷨ʵ��
template <class T>
DoublyLinkList<T>& DoublyLinkList<T>::DeleteByIndex(int k, T& x)
{
	//2����k=1ʱ��ֻ��Ҫ��ͷ����ָ����ָ��ڶ�����㣬Ȼ���ͷŵ�k����㼴��
	//3����1<k<nʱ��ֻ��Ҫ����k-1��Ԫ�ؽ���nextָ��ָ���k+1��Ԫ�ؽ�㣬Ȼ���ͷŵ�k����㼴��
	//4����k=nʱ������n-1��Ԫ�ؽ���nextָ�븳ֵΪnullptr��Ȼ���ͷŵ�k����㼴��
	if (GetData(k, x))
	{
		myLinkNode<T>* p = head->next;//pָ��ͷ���
		myLinkNode<T>* q = nullptr;//qָ��յ�ַ
		
		for (int i = 1; i < k; i++)
		{
			p = p->next;//��pָ���ƶ�����k-1�����
			if (p == nullptr)
			{
				cout << "��������Χ��" << endl;
			}
		}
		if (k == GetLength())
		{
			p->previous->next = nullptr;
			delete q;//����ɾ���ý��
		}
		else
		{
			q = p;//qָ���ɾ���ĵ�k�����
			p->previous->next = q->next;//�� ɾ����ǰ����nextָ��ָ���ɾ����һ�����
			p->next->previous = q->previous;//��ɾ������һ������previousָ��ָ���ɾ����ǰһ�����
			delete q;//����ɾ���ý��
		}
		
	}

	//1����k>n��k<1ʱ��ɾ��λ�ò���ȷ������
	else
	{
		cout << "ɾ��λ�ò���ȷ��ɾ��ʧ�ܣ�" << endl;
	}

	return *this;
}

//���ؼ���ɾ���㷨ʵ��
template <class T>
DoublyLinkList<T>& DoublyLinkList<T>::DeleteByKey(const T& x, T& y)
{
	int index = Find(x);//�õ�Ҫɾ����Ԫ��λ��

	if (index != 0)
	{
		return DeleteByIndex(index, y);
	}
	else
	{
		cout << "������û�и�Ԫ�أ�ɾ��ʧ�ܣ�" << endl;
		return *this;
	}
}

//�жϿձ��㷨ʵ��
template<class T>
bool DoublyLinkList<T>::IsEmpty() const
{
	return head->next == nullptr;
}

//��ǰ�����㷨ʵ��
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

//��λ��ȡԪ���㷨ʵ��
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

//��λ���޸�Ԫ���㷨ʵ��
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

//���ؼ��ֲ����㷨ʵ��
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

//ʵ�������ӡ�㷨
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
//���������<<
template<class T>
ostream& operator<<(ostream& out, DoublyLinkList<T>& x)
{
	x.OutPut(out);
	return out;
}


//��������յ�������
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