#pragma once
#include "Tree_Include.h"

template<typename T>

struct BinNode
{
	BinNodePosi(T) parent, lChild, rChild;//父，子
	T data; int height; int size();//高度、子树规模

	BinNodePosi(T) insertAsLC(T const&);//作为左子插入新结点
	BinNodePosi(T) insertAsRC(T const&);//作为右子插入新结点
	BinNodePosi(T) succ();//(中序遍历意义下)当前节点的直接后继

	template<typename VST> void travLevel(VST&);	//子树层次遍历
	template<typename VST> void travPre(VST&);		//子树先序遍历
	template<typename VST> void travIn(VST&);		//子树中序遍历
	template<typename VST> void travPost(VST&);		//子树后序遍历
};
hh   
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rChild = new BinNode(e, this);
}

template<typename T>
int BinNode<T>::size()
{
	//后代总数，亦即以其为根的子树的规模
	int s = 1;//计入本身
	if (lChild)
	{
		s += lChild->size();//递归计入左子树规模
	}
	if (rChild)
	{
		s += rChild->size();//递归计入右子树规模
	}
	return s;
}