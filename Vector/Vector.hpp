#pragma once
#include "Vector_Include.h"

using Rank = int;// 秩
const int DEFAULT_CAPACITY = 3;// 默认初始容量（实际应用过程中可以设置更大）

template <class T>
class Vector
{
	// 向量模板类
private:
	Rank _size;			// 规模
	int _capacity;		// 容量
	T* _elem;			// 数据区

protected:
	//Rank _size; int _capacity;  T* _elem; //规模、容量、数据区

	void copyFrom(T const* A, Rank left, Rank right); //复制数组区间A[lo, hi)

	void expand(); //空间不足时扩容

	void shrink(); //装填因子过小时压缩

	//bool bubble(Rank left, Rank right); //扫描交换
	//改进为：
	Rank bubble(Rank left, Rank right); //扫描交换

	void bubbleSort(Rank left, Rank right); //起泡排序算法

	Rank maxItem(Rank left, Rank right); //选取最大元素

	void selectionSort(Rank left, Rank right); //选择排序算法

	void merge(Rank left, Rank middle, Rank right); //归并算法

	void mergeSort(Rank left, Rank right); //归并排序算法

	void heapSort(Rank left, Rank right); //堆排序（稍后结合完全堆讲解）

	Rank partition(Rank left, Rank right); //轴点构造算法

	void quickSort(Rank left, Rank right); //快速排序算法

	void shellSort(Rank left, Rank right); //希尔排序算法

public:
	// 构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)// 容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const* A, Rank n)//数组整体复制
	{
		copyFrom(A, 0, n);
	}

	Vector(T const* A, Rank left, Rank right)//数组区间复制
	{
		copyFrom(A, left, right);
	}

	Vector(Vector<T> const& V)//向量整体复制
	{
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank left, Rank right)//向量区间复制
	{
		copyFrom(V._elem, left, right);
	}

	// 析构函数
	~Vector()
	{
		delete[] _elem;//释放内部空间
	}

	// 只读接口
	Rank size() const { return _size; }//规模

	bool empty() const { return !_size; }//判空

	int disordered() const;//判断是否有序，统计逆序对

	Rank find(T const& e) const { return find(e, 0, _size); }//无序向量整体查找

	Rank find(T const& e, Rank left, Rank right) const;//无序向量区间查找
	
	Rank search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }//有序向量整体查找

	Rank search(T const& e, Rank left, Rank right) const;//有序向量区间查找

	// 可写接口
	T& operator[](Rank r) const { return _elem[r]; }//重载下标操作符，可以类似于数组形式引用各元素

	//const T& operator[](Rank r) const { return _elem[r]; }//仅限做右值的重载版本

	Vector<T>& operator=(Vector<T> const&);//重载赋值操作符，以便直接克隆向量

	T remove(Rank r);//删除秩为r的元素

	int remove(Rank left, Rank right);//删除秩在区间[left,right)之内的元素

	Rank insert(Rank r, T const& e);//插入元素

	Rank insert(T const& e) { return insert(_size, e); }//默认作为末元素插入

	void sort(Rank left, Rank right); //对[lo, hi)排序

	void sort() { sort(0, _size); } //整体排序

	void unsort(Rank left, Rank right); //对[lo, hi)置乱

	void unsort() { unsort(0, _size); } //整体置乱

	int deduplicate(); //无序去重

	int uniquify(); //有序去重


	// 遍历接口
	void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部修改）
	
	template<typename VST>
	void traverse(VST&);//遍历（使用函数对象，可全局性修改）

};

template <typename T> 
Vector<T>& Vector<T>::operator= (Vector<T> const& V) 
{ 
	//深复制
	if (_elem) delete[] _elem; //释放原有内容
	copyFrom(V._elem, 0, V.size()); //整体复制
	return *this; //返回当前对象的引用，以便链式赋值
}


template <typename T>//T为基本类型，或已重载赋值操作符"="
void Vector<T>::copyFrom(T const* A, Rank left, Rank right)
{
	_elem = new T[_capacity = 2 * (right - left)];//分配空间
	//规模清零
	for (_size = 0; left < right; _size++, left++)//A[left,right)内元素逐一填充
	{
		_elem[_size] = A[left];//复制至 _elem[0,right-left)
	}
}
//运行时间 = O(right-left)


//扩容
template <typename T>
void Vector<T>::expand()//向量空间不足时扩充
{
	if (_size < _capacity)
	{
		return;
	}

	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//容量加倍		几何级数O（n）；		固定数值扩容	算术级数O(n^2) ;
	for (int i = 0; i < _size; i++)//复制原向量内容
	{
		_elem[i] = oldElem[i];	   //T为基本类型，或已重载赋值操作符'='
	}

	delete[] oldElem;//释放原空间
}

//缩容
template <typename T>
void Vector<T>::shrink()
{
	//装填因子过小时压缩向量所占空间
	if (_capacity < DEFAULT_CAPACITY << 1)
	{
		return; //不致收缩到DEFAULT_CAPACITY以下
	}

	if (_size << 2 > _capacity)
	{
		return; //以25%为界
	}

	T* oldElem = _elem;  //原有数据备份
	_elem = new T[_capacity >>= 1]; //容量减半

	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //复制原向量内容
	}

	delete[] oldElem; //释放原空间
}


//唯一化：算法
//应用实例：网络搜索 的局部结果经过去重操作，汇总为最终报告

// 繁琐版
//template <typename T>
//int Vector<T>::deduplicate()
//{
//	int oldSize = _size;//记录原规模
//	Rank i = 1;//从_elem[1]开始
//
//	while (i < _size)//自前向后注意考察各元素_elem[i]
//	{
//		//在前缀中寻找雷同者
//		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);//若无雷同则继续考察后继
//		//否则删除雷同(至多只有一个雷同值！)
//	}
//	return oldSize - _size;//向量规模变化了，即删除元素总数
//}
//删除无序向量中重复元素（高效版）
template <typename T>
int Vector<T>::deduplicate()
{

	int oldSize = _size; //记录原规模
	Rank i = 1; //从_elem[1]开始

	while (i < _size) //自前向后逐一考查各元素_elem[i]
	{
		if (find(_elem[i], 0, i) < 0) //在前缀[0,i)中寻找与之雷同者（至多一个）
		{
			i++; //若无雷同则继续考查其后继
		}
		else
		{
			remove(i); //否则删除当前元素
		}
	}
	return oldSize - _size; //被删除元素总数
}

template <typename T>
int Vector<T>::disordered() const
{
	int count = 0;//计数器
	for (int i = 1; i < _size; i++)//逐一检查各对相邻元素
	{
		count += (_elem[i - 1] > _elem[i]);//逆序则计数
	}
	return count;//向量有序当且仅当n = 0
}//若只需判断是否有序，则首次遇到逆序对之后即可终止


//低效算法		O(n^2)
//原因：低效的根源在于，同一元素可作为被删除元素的后继多次前移
//启示：若能以重复区间为单位，成批删除雷同元素，性能必将改进
//template<typename T>
//int Vector<T>::uniquify()
//{
//	int oldSize = _size;
//	int i = 0;					//从首元素开始
//
//	while (i < _size - 1)		//从前向后，逐一比对各对相邻元素；雷同，删除后者；否则，转至后一个元素
//	{
//		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;
//	}
//	return oldSize = _size;//向量规模变化量，即删除元素总数
//}//注意：其中_size的减小，由remove()隐式地完成

//高效版
template<typename T>
int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;//各对互异"相邻"元素的秩
	while (++j < _size)//逐一扫描，直到末元素
	//跳过雷同者；发现不同元素时，向前移至紧邻于前者右侧
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();//直接截除尾部多余元素

	return j - i;//向量规模变化量，即被删除元素总数
}//注意：通过remove(left,right)批量删除，依然不能达到高效率


//插入元素
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)		//O(n-r)
{
	expand();//如有必要，扩容
	for (int i = _size; i > r; i--)//自后向前
	{
		_elem[i] = _elem[i - 1];//后继元素顺次后移一个单元
	}
	_elem[r] = e;//置入新元素
	_size++;//更新容量

	return r;//返回秩
}

//删除元素
template <typename T>
int Vector<T>::remove(Rank left, Rank right)		//O(n-right)
{
	if (left == right)
	{
		return 0;//出于效率考虑，单独处理退化情况
	}

	while (right < _size)
	{
		_elem[left++] = _elem[right++];// [right，_size) 顺次前移 right-left 位
	}
	_size = left;//更新规模
	shrink();//若有必要，缩容

	return right - left;//返回被删除元素的数目
}

template <typename T>
T Vector<T>::remove(Rank r)
{
	//删除向量中秩为r的元素，0 <= r < size
	T e = _elem[r]; //备份被删除元素
	remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
	return e; //返回被删除元素
}


//无序向量：T为可 判等 的基本类型，或已重载操作符 == 或 !=
//有序向量：T为可 比较 的基本类型，或已重载操作符 <  或 >
//无序向量查找
template <typename T>
Rank Vector<T>::find(T const& e, Rank left, Rank right) const
//O(right - left) = O(n)   在命中多个元素时可返回 秩最大者
{
	while ((left < right--) && (e != _elem[right]));	//逆向查找

	return right;//right < left 意味着失败；否则right即命中元素的秩
}// Excel::match(e, range, type);

// 上述算法为 输入敏感(input-sensitive)算法：最好情况O(1),最坏情况O(n)


//遍历接口
//利用函数指针机制，只读或 局部性 修改
template <typename T>
void Vector<T>::traverse(void (*visit)(T&))//函数指针
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//利用函数对象机制，可 全局性修改
template <typename T>	template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}


//// 有序向量：二分查找A
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank left, Rank right)
//{
//	while (left < right)
//	{
//		Rank middle = (left + right) >> 1;//以中点为轴点
//
//		if (e < A[middle])//深入前半段[left,middle)
//		{
//			right = middle;
//		}
//		else if (A[middle] < e)//深入后半段（middle,right）
//		{
//			left = middle + 1;
//		}
//		else//在middle处找到该元素
//		{
//			cout << "使用了二分查找!" << endl;
//			return middle;
//		}
//	}
//	cout << "使用了二分查找A!" << endl;
//	return -1;//查找失败
//}

////二分查找B
////当有多个命中元素，必须返回秩最大的元素
////失败时应该返回小于目标的最大者（含[left-1]）
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank left, Rank right)
//{
//	while (1 < right - left)//有效查找区间宽度缩减到1，算法终止
//	{
//		Rank middle = (left + right) >> 1;//中点作为轴点，经过比较后确定深入
//
//		(e < A[middle]) ? right = middle : left = middle;//向左或向右
//	}//出while时，right = left + 1，查找区间仅含一个元素A[left]
//	cout << "使用了二分查找B!" << endl;
//	return (e == A[left]) > left : -1;//返回命中元素的秩 或查找失败
//}

//二分查找C
template <typename T>
static Rank binSearch(T* A, T const& e, Rank left, Rank right)
{
	while (left < right)//不变性：A[0,left] <= e < A[right,n)	A[right]总是大于目标元素的最小者
	{
		Rank middle = (left + right) >> 1;//中点作为轴点，经过比较后确定深入
		
		(e < A[middle]) ? right = middle : left = middle + 1;//左或者右
	}//出while时，A[left = right]为大于目标元素的最小元素
	cout << "使用了二分查找C!" << endl;
	return --left;//故left-1即不大于目标元素的最大秩
}

//改进版（fibonacci）
//设n = fib(k) - 1,则可以取middle = fib(k - 1) - 1;
//于是，前后子向量长度分别为fib(k - 1) - 1、fib(k - 2) - 1;
template <typename T>
static Rank fibSearch(T* A, T const& e, Rank left, Rank right)
{
	Fib fib(right - left);//创建Fibonacci数列
	while (left < right)
	{
		while (right - left < fib.get())
		{
			fib.prev();
		}
		Rank middle = left + fib.get() - 1;//黄金比例切分
		if (e < A[middle])
		{
			right = middle;
		}
		else if (A[middle] < e)
		{
			left = middle + 1;
		}
		else
		{
			cout << "使用了fibonacci查找!" << endl;
			return middle;
		}
	}
	cout << "使用了fibonacci查找!" << endl;
	return -1;
}

// 查找算法统一接口	0 <= left < right <= _size
template <typename T>
Rank Vector<T>::search(T const& e, Rank left, Rank right) const
{
	srand((unsigned int)time(NULL));
	return (rand() % 2) ?//各按百分之五十概率随机取用
		binSearch(_elem, e, left, right)//二分查找算法
		: fibSearch(_elem, e, left, right);//Fibonacci查找算法
}
//如何处置特殊情况？
//比如，目标元素不存在; 或目标元素同时存在多个；

//语义约定：
//至少，应该便于有序向量自身的维护：V.insert(1 + V.search(e),e)
//即使失败，也应该给出新元素适当插入的位置
//若允许重复元素，则每一组也需按其插入的次序排列

//约定：
//在有序向量区间V[left,right)中，确定不大于e的最后一个元素
//若 -∞ < e <V[left],则返回left-1
//若 V[right - 1] < e < +∞，则返回right-1


//BubbleSort	O(n^2)

// 初始版
//template <typename T>
//bool Vector<T>::bubble(Rank left, Rank right)
//{
//	bool sorted = true;//整体有序标志
//	while (++left < right)//自左向右，逐一检查各对相邻元素
//	{
//		if (_elem[left - 1] > _elem[left])//若逆序，则：
//		{
//			sorted = false;
//			swap(_elem[left - 1], _elem[left]);//交换
//		}
//	}
//	return sorted;//返回是否有序标志
//}
// 
//template <typename T>
//void Vector<T>::bubbleSort(Rank left, Rank right)
//{
//	while (!bubble(left, right--));//逐趟做扫描交换，直到全序
//}

// 改进版
template <typename T>
Rank Vector<T>::bubble(Rank left, Rank right)
{
	Rank last = left;//最右侧的逆序对初始化为[left-1，left]
	while (++left < right)//自左向右，逐一检查各对相邻元素
	{
		if (_elem[left - 1] > _elem[left])//若逆序，则：
		{
			
			last = left;//更新最右侧逆序对位置记录
			swap(_elem[left - 1], _elem[left]);//交换
		}
	}
	return last;//返回最右侧逆序对位置
}
template <typename T>
void Vector<T>::bubbleSort(Rank left, Rank right)
{
	while (left < (right = bubble(left, right)));
}


//MergeSort	O(nlogn)
template <typename T>
void Vector<T>::merge(Rank left, Rank middle, Rank right)
{
	T* A = _elem + left;//合并后的向量 A[0,right - left) = _elem[left,right)   存放？

	int ml = middle - left;
	T* B = new T[ml];//前子向量B[0,lm) = _elem[left,middle)

	for (Rank i = 0; i < ml; B[i] = A[i++]);//复制前子向量B

	int rm = right - middle;
	T* C = _elem + middle;//后子向量C[0,rm) = _elem[middle,right)

	for (Rank i = 0, j = 0, k = 0; (j < ml)/* || (k < rm)*/;)//B[j]和C[k]中的小者转至A的末尾
	{
		if (/*(j < ml) && */(rm <= k || (B[j] <= C[k])))//C[k]已无或不小于B[j]
		{
			A[i++] = B[j++];
		}
		if ((k < rm) && (/*ml <= j || */(B[j] > C[k])))//C[k]已无或不小于B[j]
		{
			A[i++] = C[k++];
		}
	}
	delete[] B;
}


template <typename T>
void Vector<T>::mergeSort(Rank left, Rank right)
{
	if (right - left < 2) return;//单元素区间本就自然有序，处理递归基
	int middle = (left + right) >> 1;//以中点为界

	mergeSort(left, middle);//对前半段递归排序
	mergeSort(middle, right);//对后半段递归排序
	merge(left, middle, right);//归并
}




template <typename T> 
void Vector<T>::sort(Rank left, Rank rigth) 
{ //向量区间[left, right)排序
	//srand((unsigned int)time(NULL));
	//switch (rand()%6) 
	//{
	//	case 1:  bubbleSort(left, rigth); break; //起泡排序
	//	case 2:  selectionSort(left, rigth); break; //选择排序
	//	case 3:  mergeSort(left, rigth); break; //归并排序
	//	case 4:  heapSort(left, rigth); break; //堆排序
	//	case 5:  quickSort(left, rigth); break; //快速排序
	//	default: shellSort(left, rigth); break; //希尔排序
	//}

}