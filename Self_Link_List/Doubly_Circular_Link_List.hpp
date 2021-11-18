// 02_Copy_constructor.h: Ŀ���ͷ�ļ���
//˫��ѭ��������

#pragma once
# include <iostream>

using namespace std;

template <class T>
class DoublyCirCularLinkList
{
	//template <class U>
	//friend class myLinkNode<U>;
	//�洢�����
	template <class T>
	class myLinkNode
	{
		friend class DoublyCirCularLinkList;		//����ʽ������Ϊ����
	private:
		T data;						//���Ԫ��
		myLinkNode<T>* next;			//ָ����һ������ָ��
		myLinkNode<T>* previous;		//ָ����һ����� ��ָ��
	};


public:
	DoublyCirCularLinkList();	//����
	~DoublyCirCularLinkList();	//����
	DoublyCirCularLinkList<T>& Insert(int k, const T& x);
	bool IsEmpty() const;
	//int GetLength() const;
	bool GetData(int k, T& x);
	bool ModifyData(int k, const T& x);
	int Find(const T& x);
	DoublyCirCularLinkList<T>& DeleteByIndex(int k, T& x);
	DoublyCirCularLinkList<T>& DeleteByKey(const T& x, T& y);
	void OutPut(ostream& out);

	int size = 0;


private:
	myLinkNode<T>* head;	//ָ������ĵ�һ��ͷ����ָ��
};

//���죨������˫��ѭ������
template <class T>
DoublyCirCularLinkList<T>::DoublyCirCularLinkList()
{
	head = new myLinkNode<T>();//����ͷ���
	head->next = head;
	size = 0;
}

//�����㷨ʵ��
//���ڲ���Ԫ�صĲ���Insert�����赱ǰ��������n��Ԫ�أ����ڵ�k��λ��֮ǰ������new Nodeʱ����Ҫ�������������
template <class T>
DoublyCirCularLinkList<T>& DoublyCirCularLinkList<T>::Insert(int k, const T& x)
{
	myLinkNode<T>* p = head;//pָ��ͷ���
	myLinkNode<T>* newNode = new myLinkNode<T>;//������������½��

	newNode->data = x;
	int len = size;

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

		if (p->next != head)//�ж��Ƿ���˫������β����ӽ��
		{
			p->next->previous = newNode;
		}
		newNode->previous = p;
		p->next = newNode;
		size++;
	}
	return *this;
}

//ɾ���㷨ʵ��
template <class T>
DoublyCirCularLinkList<T>& DoublyCirCularLinkList<T>::DeleteByIndex(int k, T& x)
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
			if (p == head)
			{
				cout << "��������Χ��" << endl;
			}
		}
		if (k == size)
		{
			p->previous->next = nullptr;
			delete q;//����ɾ���ý��
			size--;
		}
		else
		{
			q = p;//qָ���ɾ���ĵ�k�����
			p->previous->next = q->next;//�� ɾ����ǰ����nextָ��ָ���ɾ����һ�����
			p->next->previous = q->previous;//��ɾ������һ������previousָ��ָ���ɾ����ǰһ�����
			delete q;//����ɾ���ý��
			size--;
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
DoublyCirCularLinkList<T>& DoublyCirCularLinkList<T>::DeleteByKey(const T& x, T& y)
{
	int index = Find(x);//�õ�Ҫɾ����Ԫ��λ��

	if (index != 0)
	{
		return DeleteByIndex(index, y);
		size--;
	}
	else
	{
		cout << "������û�и�Ԫ�أ�ɾ��ʧ�ܣ�" << endl;
		return *this;
	}
}

//�жϿձ��㷨ʵ��
template<class T>
bool DoublyCirCularLinkList<T>::IsEmpty() const
{
	return head->next == head;
}

////��ǰ�����㷨ʵ��
//template <class T>
//int DoublyCirCularLinkList<T>::GetLength() const
//{
//	int length = 0;
//	myLinkNode<T>* p = head;
//	while (p->next!= head)
//	{
//		length++;
//		p = p->next;
//	}
//	return length;
//}

//��λ��ȡԪ���㷨ʵ��
template <class T>
bool DoublyCirCularLinkList<T>::GetData(int k, T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;
	if (k<1 || k>size)
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

//��λ���޸�Ԫ���㷨ʵ��
template<class T>
bool DoublyCirCularLinkList<T>::ModifyData(int k, const T& x)
{
	myLinkNode<T>* p = head->next;
	int index = 1;

	if (k<1 || k>size)
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

//���ؼ��ֲ����㷨ʵ��
template<class T>
int DoublyCirCularLinkList<T>::Find(const T& x)
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

//ʵ�������ӡ�㷨
template<class T>
void DoublyCirCularLinkList<T>::OutPut(ostream& out)
{
	myLinkNode<T>* p = head->next;
	int i = 0;

	while (i != size)
	{
		out << p->data << " ";
		p = p->next;
		i++;
	}
	cout << endl;
}
//���������<<
template<class T>
ostream& operator<<(ostream& out, DoublyCirCularLinkList<T>& x)
{
	x.OutPut(out);
	return out;
}


//��������յ�������
template <class T>
DoublyCirCularLinkList<T>::~DoublyCirCularLinkList()
{
	myLinkNode<T>* p = head->next;
	myLinkNode<T>* q = nullptr;

	int i = 0;
	while (i != size-1)
	{
		q = p;
		p = q->next;
		delete q;
	}
	head->next = head;

	delete head;
	size = 0;
}