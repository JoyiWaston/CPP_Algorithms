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
	Rank _size; int _capacity;  T* _elem; //规模、容量、数据区

	void copyFrom(T const* A, Rank left, Rank right); //复制数组区间A[lo, hi)

	void expand(); //空间不足时扩容

	void shrink(); //装填因子过小时压缩

	bool bubble(Rank left, Rank right); //扫描交换

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

	const T& operator[](Rank r) const { return _elem[r]; };//仅限做右值的重载版本

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