#pragma once
#include "Vector_Include.h"

//无序向量：T为可 判等 的基本类型，或已重载操作符 == 或 !=
//有序向量：T为可 比较 的基本类型，或已重载操作符 <  或 >

template <typename T>	
Rank Vector<T>::find(T const& e, Rank left, Rank right) const		
//O(right - left) = O(n)   在命中多个元素时可返回 秩最大者
{
	while ((left < right--) && (e != _elem[right]));	//逆向查找

	return right;//right < left 意味着失败；否则right即命中元素的秩
}// Excel::match(e, range, type);

// 上述算法为 输入敏感(input-sensitive)算法：最好情况O(1),最坏情况O(n)