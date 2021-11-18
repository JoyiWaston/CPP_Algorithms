#pragma once
#ifndef NODE
#define NODE
#include <iostream>
#include <cstring>

using namespace std;
class Node
{
public:
	Node(char* NumberOfStudent, char* NameOfStudent, int grade[]);
	Node() {};//�޲ι��캯��
	Node& GetNode();//�õ��ڵ�����
	void OutPutNode(ostream& out) const;//����ڵ�����

private:
	string StdNumber;
	string StdName;
	int Score[3];
};

//ʵ�ֹ��캯��
Node::Node(char* NumberOfStudent, char* NameOfStudent, int grade[])
{
	this->StdNumber = NumberOfStudent;
	this->StdName = NameOfStudent;
	for (int i = 0; i < 3; i++)
	{
		this->Score[i] = grade[i];
	}
}

//ʵ�ֵõ��ڵ����ݺ���
Node& Node::GetNode()
{
	return *this;
}

//ʵ������ڵ����ݺ���
void Node::OutPutNode(ostream& out) const
{
	out << "\n" << StdNumber << " " << StdName << endl;
	out << "���ģ�" << Score[0];
	out << "\t��ѧ��" << Score[1];
	out << "\tӢ�" << Score[2];
	cout << endl;
}
//���������<<
ostream& operator<<(ostream& out, const Node& x)
{
	x.OutPutNode(out);
	return out;
}
#endif
