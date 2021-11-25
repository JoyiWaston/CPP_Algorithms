#pragma once
#include "List_Include.h"
using U = unsigned int;

template <class T> 
class List 
{ 
//列表模板类
private:
	int _size; 
	ListNodePosi<T> header; 
	ListNodePosi<T> trailer; //规模、头哨兵、尾哨兵

protected:
	void init(); //列表创建时的初始化

	int clear(); //清除所有节点

	void copyNodes(ListNodePosi<T>, int); //复制列表中自位置p起的n项

	ListNodePosi<T> merge(ListNodePosi<T>, int, List<T>&, ListNodePosi<T>, int); //归并

	void mergeSort(ListNodePosi<T>&, int); //对从p开始连续的n个节点归并排序

	void selectionSort(ListNodePosi<T>, int); //对从p开始连续的n个节点选择排序

	void insertionSort(ListNodePosi<T>, int); //对从p开始连续的n个节点插入排序

	void radixSort(ListNodePosi<T>, int); //对从p开始连续的n个节点基数排序

public:
// 构造函数
	List() { init(); } //默认

	List(List<T> const& L) { copyNodes(L.first(), L._size); }//整体复制列表L

	List(List<T> const& L, Rank r, int n)//复制列表L中自第r项起的n项
	{
		ListNodePosi<T> p = L.first();
		while (0 < r--) p = p->succ;
		copyNodes(p, n);
	}

	List(ListNodePosi<T> p, int n)//复制列表中自位置p起的n项
	{
		copyNodes(p, n);
	}

 // 析构函数
	~List()//释放（包含头、尾哨兵在内的）所有节点
	{
		clear();//清空列表
		delete header;//释放头结点
		delete trailer;//释放尾结点
	}

 // 只读访问接口
	Rank size() const { return _size; } //规模

	bool empty() const { return _size <= 0; } //判空

	T& operator[] (Rank r) const//重载，支持循秩访问（效率低）
	{
		//assert: 0 <= r < size
		ListNodePosi<T> p = first(); //从首节点出发
		while (0 < r--) p = p->succ; //顺数第r个节点即是
		return p->data; //目标节点，返回其中所存元素
	}

	ListNodePosi<T> first() const { return header->succ; } //首节点位置

	ListNodePosi<T> last() const { return trailer->pred; } //末节点位置

	bool valid(ListNodePosi<T> p) //判断位置p是否对外合法
	{
		return p && (trailer != p) && (header != p);
	} //将头、尾节点等同于NULL

	ListNodePosi<T> find(T const& e) const //无序列表查找
	{
		return find(e, _size, trailer);
	}

	ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const; //无序区间查找

	ListNodePosi<T> search(T const& e) const //有序列表查找
	{
		return search(e, _size, trailer);
	}

	ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; //有序区间查找

	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //在p及其n-1个后继中选出最大者

	ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //整体最大者

 // 可写访问接口
	ListNodePosi<T> insertAsFirst(T const& e); //将e当作首节点插入

	ListNodePosi<T> insertAsLast(T const& e); //将e当作末节点插入

	ListNodePosi<T> insert(ListNodePosi<T> p, T const& e); //将e当作p的后继插入

	ListNodePosi<T> insert(T const& e, ListNodePosi<T> p); //将e当作p的前驱插入

	T remove(ListNodePosi<T> p); //删除合法位置p处的节点,返回被删除节点

	void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //全列表归并

	void sort(ListNodePosi<T> p, int n); //列表区间排序

	void sort() { sort(first(), _size); } //列表整体排序

	int deduplicate(); //无序去重

	int uniquify(); //有序去重

	void reverse(); //前后倒置（习题）

 // 遍历
	void traverse(void (*visit) (T&))//遍历，依次实施visit操作（函数指针，只读或局部性修改）
	{
		for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}

	template <typename VST> //操作器
	void traverse(VST& visit)//遍历，依次实施visit操作（函数对象，可全局性修改）
	{
		for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
}; //List
//关系运算符函数化
template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } //less than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template <typename T> static bool eq(T& a, T& b) { return a == b; } //equal



//初始化List
template <typename T> 
void List<T>::init() 
{ 
	//列表初始化，在创建列表对象时统一调用
	header = new ListNode<T>; //创建头哨兵节点
	trailer = new ListNode<T>; //创建尾哨兵节点
	
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	
	_size = 0; //记录规模
}

//清空List
template <typename T> 
int List<T>::clear() 
{ 
	//清空列表
	int oldSize = _size;
	while (0 < _size)
	{
		remove(header->succ); //反复删除首节点，直至列表变空
	}

	return oldSize;
}


//复制
template <typename T> //列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi<T> p, int n) 
{ 
	//p合法，且至少有n-1个真后继节点
	init(); //创建头、尾哨兵节点并做初始化
	while (n--) 
	{ 
		insertAsLast(p->data); 
		p = p->succ; 
	} //将起自p的n项依次作为末节点插入
}


template <typename T> 
ListNodePosi<T> List<T>::insertAsFirst(T const& e)
{
	_size++; 
	return header->insertAsSucc(e);//e当作首节点插入
} 

template <typename T> 
ListNodePosi<T> List<T>::insertAsLast(T const& e)
{
	_size++; 
	return trailer->insertAsPred(e);//e当作末节点插入
} 

template <typename T> 
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e)
{
	_size++; 
	return p->insertAsSucc(e);//e当作p的后继插入
} 

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p)
{
	_size++;
	return p->insertAsPred(e);//e当作p的前驱插入
}


//删除
template <typename T>
T List<T>::remove(ListNodePosi<T> p)//删除合法位置P处结点，并返回其数值
{
	T e = p->data;//备份待删除节点数值（设类型T可直接）
	p->pred->succ = p->succ;//待删p的后继作为p的前驱的后继
	p->succ->pred = p->pred;//待删p的前驱作为p的后继的前驱
	delete p;

	_size--;
	return e;//返回备份数值
}

//查找
//无序列表查找
template<typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const
{
	//顺序查找 O（n）
	while (0 < n--)//从左往右，逐个将p的前驱和e比对
	{
		p = p->pred;
		if (e == p->data)//直至命中或范围越界
		{
			return p;//返回命中的p
		}
	}
	return NULL;//若越界，查找失败
}

//有序列表查找
template<typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const
{
	while (0 <= n--)//对于p的最近的n个前驱，从右到左
	{
		p = p->pred;
		if (p->data <= e) break;//逐个比较
	}
	return p;//直至命中，数值越界或范围越界后，返回查找终止的位置
}//最好O(1)，最坏O(n)；等概率时平均O(n)，正比于区间宽度


//唯一化
template <typename T>
int List<T>::deduplicate()
{
	//剔除无序列表中重复的结点
	if (_size < 2) return 0;//平凡列表自然无重复

	int oldSize = _size;//记录原规模
	ListNodePosi<T> p = first(); Rank r = 1;//p从首节点起
	while (trailer != (p = p->succ))//依次直到末节点
	{
		ListNodePosi<T> q = find(p->data, r, p);//在p的r个真前驱中，查找与之相同者
		q ? remove(q) : r++;//若存在则删除；否则秩递增
	}//assert:循环过程中的任何时刻，p的所有前驱互不相同
	return oldSize - _size;//被删除元素总数
}

//有序列表唯一化 <O(n)>
template <typename T>
int List<T>::uniquify()//成批剔除重复元素
{
	if (_size < 2) return 0;//平凡列表自然无重复
	int oldSize = _size;//记录原规模
	ListNodePosi<T> p = first(); ListNodePosi<T> q;//p为各区段七点，q为其后继
	while (trailer != (q = p->succ))//反复考察紧邻的节点对(p,q)
	{
		if (p->data != q->data)
		{
			p = q;//若互异，则转向下一区段
		}
		else
		{
			remove(q);//否则（相同），删除后者
		}
	}
	return oldSize - _size;//删除元素个数
}

//排序
//选择排序
template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) 
{
	ListNodePosi<T> max = p; //最大者暂定为首节点p
	for (ListNodePosi<T> cur = p; 1 < n; n--) //从首节点p出发，将后续节点逐一与max比较
		if (!lt((cur = cur->succ)->data, max->data)) //若当前元素不小于max，则
			max = cur; //更新最大元素位置记录
	return max; //返回最大节点位置
}
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) { //valid(p) && rank(p) + n <= size
   /*DSA*///printf ( "SelectionSort ...\n" );
	ListNodePosi<T> head = p->pred, tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; //待排序区间为(head, tail)
	while (1 < n) { //在至少还剩两个节点之前，在待排序区间内
		ListNodePosi<T> max = selectMax(head->succ, n); //找出最大者（歧义时后者优先）
		insert(remove(max), tail); //将其移至无序区间末尾（作为有序区间新的首元素）
		/*DSA*///swap(tail->pred->data, selectMax( head->succ, n )->data );
		tail = tail->pred; n--;
	}
}

//插入排序
template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
	for (int r = 0; r < n; r++)
	{
		//逐一引入各结点，由Sr得到Sr+1
		insert(search(p->data, r, p), p->data);//查找+插入
		p = p->succ;
		remove(p->pred);//转向下一节点
	}//n次迭代，每次O（r+1）
}//仅使用O（1）辅助空间，属于就地算法

//归并排序
template <typename T> //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T>& L, ListNodePosi<T> q, int m) 
{
	// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
	//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
	// 注意：在被mergeSort()调用时，this == &L && rank(p) + n = rank(q)
	ListNodePosi<T> pp = p->pred; //归并之后p可能不再指向首节点，故需先记忆，以便在返回前更新
	while ((0 < m) && (q != p)) //q尚未出界（或在mergeSort()中，p亦尚未出界）之前
	{
		if ((0 < n) && (p->data <= q->data)) //若p尚未出界且v(p) <= v(q)，则
		{
			p = p->succ; n--;
		} //p直接后移，即完成归入
		else //否则，将q转移至p之前，以完成归入
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	}
	return pp->succ; //更新的首节点
}
template <typename T> //列表的归并排序算法：对起始于位置p的n个元素排序
void List<T>::mergeSort(ListNodePosi<T>& p, int n) 
{ 
	//valid(p) && rank(p) + n <= size
	if (n < 2) return; //若待排序范围已足够小，则直接返回；否则...
	int m = n >> 1; //以中点为界
	ListNodePosi<T> q = p; for (int i = 0; i < m; i++) q = q->succ; //找到后子列表起点
	mergeSort(p, m); mergeSort(q, n - m); //前、后子列表各分别排序
	p = merge(p, m, *this, q, n - m); //归并
} //注意：排序后，p依然指向归并后区间的（新）起点

//基数排序
template <typename T> //对列表中起始于位置p、宽度为n的区间做基数排序
void List<T>::radixSort(ListNodePosi<T> p, int n) 
{ 
	ListNodePosi<T> head = p->pred; 
	ListNodePosi<T> tail = p;

	for (int i = 0; i < n; i++) tail = tail->succ; //待排序区间为(head, tail)
	
	for (U radixBit = 0x1; radixBit && (p = head); radixBit <<= 1) //以下反复地
	{
		for (int i = 0; i < n; i++) //根据当前基数位，将所有节点
		{
			radixBit& U(p->succ->data) ? //分拣为后缀（1）与前缀（0）
				insert(remove(p->succ), tail) : p = p->succ;
		}
	}
}
//思考：某趟分拣后若前缀、后缀没有变化，是否可以随即结束算法？
//待改进：提前找出最大元素并估算出最高有效位，从而节省无用的分拣
//待改进：为避免remove()、insertB()的低效率，实现List::moveB(t,p)接口，将节点p移动至t之前

template <typename T> 
void List<T>::sort(ListNodePosi<T> p, int n) 
{ 
	//列表区间排序
	srand((unsigned int)time(NULL));
	switch (rand() % 4) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充
	case 1:  insertionSort(p, n); break; //插入排序
	case 2:  selectionSort(p, n); break; //选择排序
	case 3:  mergeSort(p, n); break; //归并排序
	default: radixSort(p, n); break; //基数排序
	}
}