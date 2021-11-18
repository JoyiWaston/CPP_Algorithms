#include "Linear_List.hpp"
#include "Node.h"

//线性表应用：
//1、依次插入100，200，300，400
//2、读取并输出表中第三个元素的值，判断元素100在表中的位置
//3、将100改成150，删除200和400后，显示当前表的相关信息
void test01()
{
	//创建MaxSize=10 的线性表
	LinearList<int> IntegerLList(10);

	int x, y, z;

	//依次插入100，200，300，400到线性表中
	IntegerLList.Insert(1, 100);
	IntegerLList.Insert(2, 200);
	IntegerLList.Insert(3, 300);
	IntegerLList.Insert(4, 400);

	//当前表状态
	cout << "当前表长度：" << IntegerLList.GetLength() << endl;
	cout << "当前表遍历结果为：" << IntegerLList;

	//读取并输出表中第三个元素的值，判断元素100在表中的位置
	IntegerLList.GetData(3, x);
	cout << "表中第三个元素为：" << x << endl;
	cout << IntegerLList.Find(100) << endl;

	IntegerLList.ModifyData(1, 150);

	IntegerLList.DeleteByIndex(2, y);
	cout << y << endl;

	IntegerLList.DeleteByKey(400, z);
	cout << z << endl;

	cout << "当前表遍历结果为：" << IntegerLList;

}

//复杂线性表应用：
//线性表中每一个数据元素表示一名学生的信息，包括学号、姓名和3门课程（语数英）成绩。
//对于一个最多由十个这样的数据元素构成的线性表，采用顺序存储结构，进行如下操作：
//1、将两个结点插入表中
//2、显示当前表的状态
//3、将表中第二个元素输出
//4、删除表中第二个元素，修改表中第一个元素的信息，显示当前表的状态
void test02()
{
	srand((unsigned int)time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	int z = rand() % 100 + 1;

	LinearList<Node> NodeList(10);//最多有10个以Node对象为数据元素的顺序表
	int grade1[3] = { x,y,z };
	int grade2[3] = { y,z,x };
	int grade3[3] = { z,x,y };

	Node Node1("001", "院枚潮", grade1);
	Node Node2("002", "杨立  ", grade2);
	Node Node3("003", "段金成", grade3);
	Node o;

	//将两个结点插入表中
	NodeList.Insert(1, Node1);
	NodeList.Insert(2, Node2);

	//显示当前表的状态
	cout << "当前表的长度为：" << NodeList.GetLength() << endl;
	cout << "\n当前表的元素为：" << NodeList;

	//将表中第二个元素输出
	NodeList.GetData(2, o);
	cout << "表中第二个元素为：" << o << endl;

	//删除表中第二个元素，修改第一个元素信息，显示当前表状态
	NodeList.DeleteByIndex(2, o);
	cout << "删除了：\n" << o << endl;
	NodeList.ModifyData(1, Node3);

	cout << "当前表的长度为：" << NodeList.GetLength() << endl;
	cout << "\n当前表的元素为：" << NodeList;

}


int main()
{
	cout << "-----------------------test01-----------------------" << endl;
	test01();
	cout << "-----------------------test02-----------------------" << endl;
	test02();

	return 0;
}
