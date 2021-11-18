// 02_Copy_constructor.cpp: 目标的源文件。
//链表应用

#include "Singly_Link_List.hpp"
#include "W:\\C++_Workspace\\Cplusplus_Algorithms\\Cplusplus_Algorithms\\01_Destructor\\Node.h"
#include "Circular_Link_List.hpp"
#include "Doubly_Link_ List.hpp"
#include "Doubly_Circular_Link_List.hpp"

//单项链表应用:
//1、依次插入100，200，300，400。显示当前表的相关信息
//2、读取并输出表中第3个元素的值，判断元素100在表中的位置
//3、删除200和400后，显示当前表的相关信息
//4、删除表中第二个元素，修改表中第一个元素的信息，显示当前表的状态
void test01()
{
	SinglyLinkList<int> L1;
	int x, y;

	L1.Insert(1, 100);
	L1.Insert(2, 200);
	L1.Insert(3, 300);
	L1.Insert(4, 400);

	cout << "当前表状态为：" << L1;

	L1.GetData(3, x);
	cout << "表中第三个元素的值为：" << x << endl;

	y = L1.Find(100);
	cout << "元素100在表中的位置为：" << x << endl;

	L1.DeleteByKey(200, y);
	cout << "刚刚删除了：" << y << endl;
	cout << "当前表状态为：" << L1;

	L1.DeleteByKey(400, y);
	cout << "刚刚删除了：" << y << endl;
	cout << "当前表状态为：" << L1;

	L1.DeleteByIndex(2, y);
	cout << "刚刚删除了：" << y << endl;
	cout << "当前表状态为：" << L1;

	L1.ModifyData(1, x);
	cout << "刚刚修改了：" << x << endl;
	cout << "当前表状态为：" << L1;
}

//复杂数据类型单项链表应用：
//线性表中每一个数据元素表示一名学生的信息，包括学号、姓名和3门课程（语数英）成绩。
//对于一个由这样的数据元素构成的线性表，采用单向链表存储结构，进行如下操作：
//1、将两个结点插入表中
//2、显示当前表的状态
//3、将表中第二个元素输出
//4、删除表中第二个元素，修改表中第一个元素的信息，显示当前表的状态
void test02()
{
	SinglyLinkList<Node> S1;

	srand((unsigned int)time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	int z = rand() % 100 + 1;

	int grade1[3] = { x,y,z };
	int grade2[3] = { y,z,x };
	int grade3[3] = { z,x,y };

	Node Node1("001", "院枚潮", grade1);
	Node Node2("002", "杨立  ", grade2);
	Node Node3("003", "段金成", grade3);
	Node o;

	//将两个结点插入表中
	S1.Insert(1, Node1);
	S1.Insert(2, Node2);
	
	//显示当前表状态
	cout << "当前表长度为：\n" << S1.GetLength() << endl;
	cout << "当前表元素为：\n" << S1;

	//将表中第二个元素输出
	S1.GetData(2, o);
	cout << "表中第二个元素为：\n" << o;

	//删除表中第二个元素，修改第一个元素信息，显示当前表状态
	S1.DeleteByIndex(2, o);
	cout << "删除了：\n" << o << endl;
	S1.ModifyData(1, Node3);

	cout << "当前表的长度为：" << S1.GetLength() << endl;
	cout << "\n当前表的元素为：" << S1;
}

//双向链表测试
void test03()
{
	DoublyLinkList<Node> D1;

	srand((unsigned int)time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	int z = rand() % 100 + 1;

	int grade1[3] = { x,y,z };
	int grade2[3] = { y,z,x };
	int grade3[3] = { z,x,y };

	Node Node1("001", "院枚潮", grade1);
	Node Node2("002", "杨立  ", grade2);
	Node Node3("003", "段金成", grade3);
	Node o;

	//将两个结点插入表中
	D1.Insert(1, Node1);
	D1.Insert(2, Node2);
	/*D1.Insert(3, Node3);*/

	//显示当前表状态
	cout << "当前表长度为：\n" << D1.GetLength() << endl;
	cout << "当前表元素为：\n" << D1;

	//将表中第二个元素输出
	D1.GetData(2, o);
	cout << "表中第二个元素为：\n" << o;

	//删除表中第二个元素，修改第一个元素信息，显示当前表状态
	D1.DeleteByIndex(2, o);
	cout << "删除了：\n" << o << endl;
	D1.ModifyData(1, Node3);

	cout << "当前表的长度为：" << D1.GetLength() << endl;
	cout << "\n当前表的元素为：" << D1;
}

//循环链表测试
void test04()
{
	CircularLinkList<Node> C1;

	srand((unsigned int)time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	int z = rand() % 100 + 1;

	int grade1[3] = { x,y,z };
	int grade2[3] = { y,z,x };
	int grade3[3] = { z,x,y };

	Node Node1("001", "院枚潮", grade1);
	Node Node2("002", "杨立  ", grade2);
	Node Node3("003", "段金成", grade3);
	Node o;

	//将两个结点插入表中
	C1.Insert(1, Node1);
	C1.Insert(2, Node2);
	/*C1.Insert(3, Node3);*/

	//显示当前表状态
	cout << "当前表长度为：\n" << C1.GetLength() << endl;
	cout << "当前表元素为：\n" << C1;

	//将表中第二个元素输出
	C1.GetData(2, o);
	cout << "表中第二个元素为：\n" << o;

	//删除表中第二个元素，修改第一个元素信息，显示当前表状态
	C1.DeleteByIndex(2, o);
	cout << "删除了：\n" << o << endl;
	C1.ModifyData(1, Node3);

	cout << "当前表的长度为：" << C1.GetLength() << endl;
	cout << "\n当前表的元素为：" << C1;
}

//双向循环链表
void test05()
{
	DoublyCirCularLinkList<Node> DC1;

	srand((unsigned int)time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	int z = rand() % 100 + 1;

	int grade1[3] = { x,y,z };
	int grade2[3] = { y,z,x };
	int grade3[3] = { z,x,y };

	Node Node1("001", "院枚潮", grade1);
	Node Node2("002", "杨立  ", grade2);
	Node Node3("003", "段金成", grade3);
	Node o;

	//将两个结点插入表中
	DC1.Insert(1, Node1);
	DC1.Insert(2, Node2);
	/*DC1.Insert(3, Node3);*/

	//显示当前表状态
	cout << "当前表长度为：\n" << DC1.size << endl;
	cout << "当前表元素为：\n" << DC1;

	//将表中第二个元素输出
	DC1.GetData(2, o);
	cout << "表中第二个元素为：\n" << o;

	//删除表中第二个元素，修改第一个元素信息，显示当前表状态
	DC1.DeleteByIndex(2, o);
	cout << "删除了：\n" << o << endl;
	DC1.ModifyData(1, Node3);

	cout << "当前表的长度为：" << DC1 << endl;
	cout << "\n当前表的元素为：" << DC1;
}




int main()
{
	cout << "-----------------------test01-----------------------" << endl;
	test01();
	cout << "-----------------------test02-----------------------" << endl;
	test02();
	cout << "-----------------------test03-----------------------" << endl;
	test03();
	cout << "-----------------------test04-----------------------" << endl;
	test04();
	cout << "-----------------------test05-----------------------" << endl;
	test05();

	return 0;
}
