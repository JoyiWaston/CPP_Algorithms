#pragma once
# include <iostream>

using namespace std;

template <class T>
class CircularLinkList
{
	//template <class U>
	//friend class myLinkNode<U>;
	//�洢�����
	template <class T>
	class myLinkNode
	{
		friend class CircularLinkList;		//����ʽ������Ϊ����

	public:
		myLinkNode()	//���캯��
		{
			next = nullptr;
		}

	private:
		T data;						//���Ԫ��
		myLinkNode<T>* next;			//ָ����һ������ָ��
	};


public:
	CircularLinkList();	//����
	~CircularLinkList();	//����
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
	myLinkNode<T>* head;	//ָ������ĵ�һ��ͷ����ָ��
};

//���죨����ѭ������
template <class T>
CircularLinkList<T>::CircularLinkList()
{
	head = new myLinkNode<T>();//����ͷ���
	head->next = head;
}

//�����㷨ʵ��
//���ڲ���Ԫ�صĲ���Insert�����赱ǰ��������n��Ԫ�أ����ڵ�k��λ��֮ǰ������new Nodeʱ����Ҫ�������������
template <class T>
CircularLinkList<T>& CircularLinkList<T>::Insert(int k, const T& x)
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
		p->next = newNode;
	}

	return *this;
}

//ɾ���㷨ʵ��
template <class T>
CircularLinkList<T>& CircularLinkList<T>::DeleteByIndex(int k, T& x)
{
	//2����k=1ʱ��ֻ��Ҫ��ͷ����ָ����ָ��ڶ�����㣬Ȼ���ͷŵ�k����㼴��
	//3����1<k<nʱ��ֻ��Ҫ����k-1��Ԫ�ؽ���nextָ��ָ���k+1��Ԫ�ؽ�㣬Ȼ���ͷŵ�k����㼴��
	//4����k=nʱ������n-1��Ԫ�ؽ���nextָ�븳ֵΪnullptr��Ȼ���ͷŵ�k����㼴��
	if (GetData(k, x))
	{
		myLinkNode<T>* p = head;//pָ��ͷ���
		myLinkNode<T>* q = nullptr;//qָ��յ�ַ
		for (int i = 1; i < k; i++)
		{
			p = p->next;//��pָ���ƶ�����k-1�����
		}
		q = p->next;//qָ���ɾ���ĵ�k�����
		p->next = q->next;//����k�������������Ƴ�
		delete q;//����ɾ���ý��
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
CircularLinkList<T>& CircularLinkList<T>::DeleteByKey(const T& x, T& y)
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
bool CircularLinkList<T>::IsEmpty() const
{
	return head->next == head;
}

//��ǰ�����㷨ʵ��
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

//��λ��ȡԪ���㷨ʵ��
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

//��λ���޸�Ԫ���㷨ʵ��
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

//���ؼ��ֲ����㷨ʵ��
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

//ʵ�������ӡ�㷨
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
//���������<<
template<class T>
ostream& operator<<(ostream& out, CircularLinkList<T>& x)
{
	x.OutPut(out);
	return out;
}

//���������ѭ������
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
	delete head;//�ͷ�ͷ���
}