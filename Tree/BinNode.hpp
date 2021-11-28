#pragma once
#include "Tree_Include.h"

template<typename T>

struct BinNode
{
	BinNodePosi(T) parent, lChild, rChild;//������
	T data; int height; int size();//�߶ȡ�������ģ

	BinNodePosi(T) insertAsLC(T const&);//��Ϊ���Ӳ����½��
	BinNodePosi(T) insertAsRC(T const&);//��Ϊ���Ӳ����½��
	BinNodePosi(T) succ();//(�������������)��ǰ�ڵ��ֱ�Ӻ��

	template<typename VST> void travLevel(VST&);	//������α���
	template<typename VST> void travPre(VST&);		//�����������
	template<typename VST> void travIn(VST&);		//�����������
	template<typename VST> void travPost(VST&);		//�����������
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
	//����������༴����Ϊ���������Ĺ�ģ
	int s = 1;//���뱾��
	if (lChild)
	{
		s += lChild->size();//�ݹ������������ģ
	}
	if (rChild)
	{
		s += rChild->size();//�ݹ������������ģ
	}
	return s;
}