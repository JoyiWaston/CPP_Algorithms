#pragma once
#include "Vector_Include.h"

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