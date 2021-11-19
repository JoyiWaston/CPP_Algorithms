#pragma once
#include "Vector_Include.h"


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