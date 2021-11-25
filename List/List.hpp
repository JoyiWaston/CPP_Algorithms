#pragma once
#include "List_Include.h"
using U = unsigned int;

template <class T> 
class List 
{ 
//�б�ģ����
private:
	int _size; 
	ListNodePosi<T> header; 
	ListNodePosi<T> trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
	void init(); //�б���ʱ�ĳ�ʼ��

	int clear(); //������нڵ�

	void copyNodes(ListNodePosi<T>, int); //�����б�����λ��p���n��

	ListNodePosi<T> merge(ListNodePosi<T>, int, List<T>&, ListNodePosi<T>, int); //�鲢

	void mergeSort(ListNodePosi<T>&, int); //�Դ�p��ʼ������n���ڵ�鲢����

	void selectionSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ�ѡ������

	void insertionSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ��������

	void radixSort(ListNodePosi<T>, int); //�Դ�p��ʼ������n���ڵ��������

public:
// ���캯��
	List() { init(); } //Ĭ��

	List(List<T> const& L) { copyNodes(L.first(), L._size); }//���帴���б�L

	List(List<T> const& L, Rank r, int n)//�����б�L���Ե�r�����n��
	{
		ListNodePosi<T> p = L.first();
		while (0 < r--) p = p->succ;
		copyNodes(p, n);
	}

	List(ListNodePosi<T> p, int n)//�����б�����λ��p���n��
	{
		copyNodes(p, n);
	}

 // ��������
	~List()//�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
	{
		clear();//����б�
		delete header;//�ͷ�ͷ���
		delete trailer;//�ͷ�β���
	}

 // ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ

	bool empty() const { return _size <= 0; } //�п�

	T& operator[] (Rank r) const//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	{
		//assert: 0 <= r < size
		ListNodePosi<T> p = first(); //���׽ڵ����
		while (0 < r--) p = p->succ; //˳����r���ڵ㼴��
		return p->data; //Ŀ��ڵ㣬������������Ԫ��
	}

	ListNodePosi<T> first() const { return header->succ; } //�׽ڵ�λ��

	ListNodePosi<T> last() const { return trailer->pred; } //ĩ�ڵ�λ��

	bool valid(ListNodePosi<T> p) //�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (trailer != p) && (header != p);
	} //��ͷ��β�ڵ��ͬ��NULL

	ListNodePosi<T> find(T const& e) const //�����б����
	{
		return find(e, _size, trailer);
	}

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const; //�����������

	ListNodePosi<T> search(T const& e) const //�����б����
	{
		return search(e, _size, trailer);
	}

	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; //�����������

	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //��p����n-1�������ѡ�������

	ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //���������

 // ��д���ʽӿ�
	ListNodePosi<T> insertAsFirst(T const& e); //��e�����׽ڵ����

	ListNodePosi<T> insertAsLast(T const& e); //��e����ĩ�ڵ����

	ListNodePosi<T> insert(ListNodePosi<T> p, T const& e); //��e����p�ĺ�̲���

	ListNodePosi<T> insert(T const& e, ListNodePosi<T> p); //��e����p��ǰ������

	T remove(ListNodePosi<T> p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�

	void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //ȫ�б�鲢

	void sort(ListNodePosi<T> p, int n); //�б���������

	void sort() { sort(first(), _size); } //�б���������

	int deduplicate(); //����ȥ��

	int uniquify(); //����ȥ��

	void reverse(); //ǰ���ã�ϰ�⣩

 // ����
	void traverse(void (*visit) (T&))//����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	{
		for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}

	template <typename VST> //������
	void traverse(VST& visit)//����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
	{
		for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
}; //List
//��ϵ�����������
template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } //less than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template <typename T> static bool eq(T& a, T& b) { return a == b; } //equal



//��ʼ��List
template <typename T> 
void List<T>::init() 
{ 
	//�б��ʼ�����ڴ����б����ʱͳһ����
	header = new ListNode<T>; //����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>; //����β�ڱ��ڵ�
	
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	
	_size = 0; //��¼��ģ
}

//���List
template <typename T> 
int List<T>::clear() 
{ 
	//����б�
	int oldSize = _size;
	while (0 < _size)
	{
		remove(header->succ); //����ɾ���׽ڵ㣬ֱ���б���
	}

	return oldSize;
}


//����
template <typename T> //�б��ڲ������������б�����λ��p���n��
void List<T>::copyNodes(ListNodePosi<T> p, int n) 
{ 
	//p�Ϸ�����������n-1�����̽ڵ�
	init(); //����ͷ��β�ڱ��ڵ㲢����ʼ��
	while (n--) 
	{ 
		insertAsLast(p->data); 
		p = p->succ; 
	} //������p��n��������Ϊĩ�ڵ����
}


template <typename T> 
ListNodePosi<T> List<T>::insertAsFirst(T const& e)
{
	_size++; 
	return header->insertAsSucc(e);//e�����׽ڵ����
} 

template <typename T> 
ListNodePosi<T> List<T>::insertAsLast(T const& e)
{
	_size++; 
	return trailer->insertAsPred(e);//e����ĩ�ڵ����
} 

template <typename T> 
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e)
{
	_size++; 
	return p->insertAsSucc(e);//e����p�ĺ�̲���
} 

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p)
{
	_size++;
	return p->insertAsPred(e);//e����p��ǰ������
}


//ɾ��
template <typename T>
T List<T>::remove(ListNodePosi<T> p)//ɾ���Ϸ�λ��P����㣬����������ֵ
{
	T e = p->data;//���ݴ�ɾ���ڵ���ֵ��������T��ֱ�ӣ�
	p->pred->succ = p->succ;//��ɾp�ĺ����Ϊp��ǰ���ĺ��
	p->succ->pred = p->pred;//��ɾp��ǰ����Ϊp�ĺ�̵�ǰ��
	delete p;

	_size--;
	return e;//���ر�����ֵ
}

//����
//�����б����
template<typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const
{
	//˳����� O��n��
	while (0 < n--)//�������ң������p��ǰ����e�ȶ�
	{
		p = p->pred;
		if (e == p->data)//ֱ�����л�ΧԽ��
		{
			return p;//�������е�p
		}
	}
	return NULL;//��Խ�磬����ʧ��
}

//�����б����
template<typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const
{
	while (0 <= n--)//����p�������n��ǰ�������ҵ���
	{
		p = p->pred;
		if (p->data <= e) break;//����Ƚ�
	}
	return p;//ֱ�����У���ֵԽ���ΧԽ��󣬷��ز�����ֹ��λ��
}//���O(1)���O(n)���ȸ���ʱƽ��O(n)��������������


//Ψһ��
template <typename T>
int List<T>::deduplicate()
{
	//�޳������б����ظ��Ľ��
	if (_size < 2) return 0;//ƽ���б���Ȼ���ظ�

	int oldSize = _size;//��¼ԭ��ģ
	ListNodePosi<T> p = first(); Rank r = 1;//p���׽ڵ���
	while (trailer != (p = p->succ))//����ֱ��ĩ�ڵ�
	{
		ListNodePosi<T> q = find(p->data, r, p);//��p��r����ǰ���У�������֮��ͬ��
		q ? remove(q) : r++;//��������ɾ���������ȵ���
	}//assert:ѭ�������е��κ�ʱ�̣�p������ǰ��������ͬ
	return oldSize - _size;//��ɾ��Ԫ������
}

//�����б�Ψһ�� <O(n)>
template <typename T>
int List<T>::uniquify()//�����޳��ظ�Ԫ��
{
	if (_size < 2) return 0;//ƽ���б���Ȼ���ظ�
	int oldSize = _size;//��¼ԭ��ģ
	ListNodePosi<T> p = first(); ListNodePosi<T> q;//pΪ�������ߵ㣬qΪ����
	while (trailer != (q = p->succ))//����������ڵĽڵ��(p,q)
	{
		if (p->data != q->data)
		{
			p = q;//�����죬��ת����һ����
		}
		else
		{
			remove(q);//������ͬ����ɾ������
		}
	}
	return oldSize - _size;//ɾ��Ԫ�ظ���
}

//����
//ѡ������
template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) 
{
	ListNodePosi<T> max = p; //������ݶ�Ϊ�׽ڵ�p
	for (ListNodePosi<T> cur = p; 1 < n; n--) //���׽ڵ�p�������������ڵ���һ��max�Ƚ�
		if (!lt((cur = cur->succ)->data, max->data)) //����ǰԪ�ز�С��max����
			max = cur; //�������Ԫ��λ�ü�¼
	return max; //�������ڵ�λ��
}
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) { //valid(p) && rank(p) + n <= size
   /*DSA*///printf ( "SelectionSort ...\n" );
	ListNodePosi<T> head = p->pred, tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; //����������Ϊ(head, tail)
	while (1 < n) { //�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
		ListNodePosi<T> max = selectMax(head->succ, n); //�ҳ�����ߣ�����ʱ�������ȣ�
		insert(remove(max), tail); //����������������ĩβ����Ϊ���������µ���Ԫ�أ�
		/*DSA*///swap(tail->pred->data, selectMax( head->succ, n )->data );
		tail = tail->pred; n--;
	}
}

//��������
template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
	for (int r = 0; r < n; r++)
	{
		//��һ�������㣬��Sr�õ�Sr+1
		insert(search(p->data, r, p), p->data);//����+����
		p = p->succ;
		remove(p->pred);//ת����һ�ڵ�
	}//n�ε�����ÿ��O��r+1��
}//��ʹ��O��1�������ռ䣬���ھ͵��㷨

//�鲢����
template <typename T> //�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T>& L, ListNodePosi<T> q, int m) 
{
	// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
	//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
	// ע�⣺�ڱ�mergeSort()����ʱ��this == &L && rank(p) + n = rank(q)
	ListNodePosi<T> pp = p->pred; //�鲢֮��p���ܲ���ָ���׽ڵ㣬�����ȼ��䣬�Ա��ڷ���ǰ����
	while ((0 < m) && (q != p)) //q��δ���磨����mergeSort()�У�p����δ���磩֮ǰ
	{
		if ((0 < n) && (p->data <= q->data)) //��p��δ������v(p) <= v(q)����
		{
			p = p->succ; n--;
		} //pֱ�Ӻ��ƣ�����ɹ���
		else //���򣬽�qת����p֮ǰ������ɹ���
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	}
	return pp->succ; //���µ��׽ڵ�
}
template <typename T> //�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNodePosi<T>& p, int n) 
{ 
	//valid(p) && rank(p) + n <= size
	if (n < 2) return; //��������Χ���㹻С����ֱ�ӷ��أ�����...
	int m = n >> 1; //���е�Ϊ��
	ListNodePosi<T> q = p; for (int i = 0; i < m; i++) q = q->succ; //�ҵ������б����
	mergeSort(p, m); mergeSort(q, n - m); //ǰ�������б���ֱ�����
	p = merge(p, m, *this, q, n - m); //�鲢
} //ע�⣺�����p��Ȼָ��鲢������ģ��£����

//��������
template <typename T> //���б�����ʼ��λ��p�����Ϊn����������������
void List<T>::radixSort(ListNodePosi<T> p, int n) 
{ 
	ListNodePosi<T> head = p->pred; 
	ListNodePosi<T> tail = p;

	for (int i = 0; i < n; i++) tail = tail->succ; //����������Ϊ(head, tail)
	
	for (U radixBit = 0x1; radixBit && (p = head); radixBit <<= 1) //���·�����
	{
		for (int i = 0; i < n; i++) //���ݵ�ǰ����λ�������нڵ�
		{
			radixBit& U(p->succ->data) ? //�ּ�Ϊ��׺��1����ǰ׺��0��
				insert(remove(p->succ), tail) : p = p->succ;
		}
	}
}
//˼����ĳ�˷ּ����ǰ׺����׺û�б仯���Ƿ�����漴�����㷨��
//���Ľ�����ǰ�ҳ����Ԫ�ز�����������Чλ���Ӷ���ʡ���õķּ�
//���Ľ���Ϊ����remove()��insertB()�ĵ�Ч�ʣ�ʵ��List::moveB(t,p)�ӿڣ����ڵ�p�ƶ���t֮ǰ

template <typename T> 
void List<T>::sort(ListNodePosi<T> p, int n) 
{ 
	//�б���������
	srand((unsigned int)time(NULL));
	switch (rand() % 4) { //���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������
	case 1:  insertionSort(p, n); break; //��������
	case 2:  selectionSort(p, n); break; //ѡ������
	case 3:  mergeSort(p, n); break; //�鲢����
	default: radixSort(p, n); break; //��������
	}
}