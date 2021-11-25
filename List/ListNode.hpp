#pragma once

using Rank = int; //��
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; //�б�ڵ�λ��
template <typename T> 
struct ListNode 
{ 
    //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
    // ��Ա
    T data; 
    ListNodePosi<T> pred; 
    ListNodePosi<T> succ; //��ֵ��ǰ�������

    // ���캯��
    ListNode() {} //���header��trailer�Ĺ���
    ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL)
        : data(e), pred(p), succ(s) {} //Ĭ�Ϲ�����

    // �����ӿ�
    ListNodePosi<T> insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
    ListNodePosi<T> insertAsSucc(T const& e); //���浱ǰ�ڵ�֮������½ڵ�
};


//��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
template <typename T> 
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e) 
{
    ListNodePosi<T> x = new ListNode(e, pred, this); //�����½ڵ�
    pred->succ = x; 
    pred = x; //������������\

    return x; //�����½ڵ��λ��
}


//��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
template <typename T> 
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e) 
{
    ListNodePosi<T> x = new ListNode(e, this, succ); //�����½ڵ�
    succ->pred = x; 
    succ = x; //������������

    return x; //�����½ڵ��λ��
}