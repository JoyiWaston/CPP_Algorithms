#pragma once
#define stature(p) ((p) ? (p)->height : -1)
#include "BinNode.hpp"


template<class T>
class BinTree
{
protected:
	int _size;//��ģ
	BinNodePosi(T) _root;//���ڵ�
	virtual int updateHeight(BinNodePosi(T) x);//���½ڵ� x �ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);//����x�����ȵĸ߶�

public:
	int size() const { return _size; }//��ģ
	bool empty() const { return _root; }//�п�
	BinNodePosi(T) root() const { return _root; }//����

	//�������룬ɾ���ͷ��봰��
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);

	//�����ӿ�

};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)//���½ڵ�x�ĸ߶ȣ��������������ͬ����
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T> ::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)//���Ż���һ���߶�δ�䣬������ֹ
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