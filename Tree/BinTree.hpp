#pragma once
#define stature(p) ((p) ? (p)->height : -1)
#include "BinNode.hpp"


template<class T>
class BinTree
{
protected:
	int _size;//规模
	BinNodePosi(T) _root;//根节点
	virtual int updateHeight(BinNodePosi(T) x);//更新节点 x 的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新x及祖先的高度

public:
	int size() const { return _size; }//规模
	bool empty() const { return _root; }//判空
	BinNodePosi(T) root() const { return _root; }//树根

	//子树接入，删除和分离窗口
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);

	//遍历接口

};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)//更新节点x的高度，具体规则因树不同而异
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T> ::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)//可优化：一旦高度未变，即可终止
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNodePosi(T) BinTree<T> ::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
BinNodePosi(T) BinTree<T> ::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}