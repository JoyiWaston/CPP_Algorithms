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
	Node() {};//无参构造函数
	Node& GetNode();//得到节点数据
	void OutPutNode(ostream& out) const;//输出节点数据

private:
	string StdNumber;
	string StdName;
	int Score[3];
};

//实现构造函数
Node::Node(char* NumberOfStudent, char* NameOfStudent, int grade[])
{
	this->StdNumber = NumberOfStudent;
	this->StdName = NameOfStudent;
	for (int i = 0; i < 3; i++)
	{
		this->Score[i] = grade[i];
	}
}

//实现得到节点数据函数
Node& Node::GetNode()
{
	return *this;
}

//实现输出节点数据函数
void Node::OutPutNode(ostream& out) const
{
	out << "\n" << StdNumber << " " << StdName << endl;
	out << "语文：" << Score[0];
	out << "\t数学：" << Score[1];
	out << "\t英语：" << Score[2];
	cout << endl;
}
//重载运算符<<
ostream& operator<<(ostream& out, const Node& x)
{
	x.OutPutNode(out);
	return out;
}
#endif
