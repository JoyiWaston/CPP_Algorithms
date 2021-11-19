#pragma once
#include "Vector_Include.h"

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