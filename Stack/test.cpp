#include "Stack.hpp"

//1、进制转换（逆序输出）
void convert(Stack<char>& S, __int64 n, int base)
{
	static char digit[] = //新进制下的数位符号，可视为base取值范围适当扩充
	{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (n > 0)//由低到高，逐一计算处新进制下的各数位
	{
		S.push(digit[n % base]);//余数（对应数位）入栈
		n /= base;//n更新为其对base的除商
	}
}
void test01()
{
	int n = 10;
	int base = 3;

	Stack<char> S;
	convert(S, n, base);//用栈记录转换得到的位数
	while (!S.empty())
	{
		cout << S.pop() << " ";
	}
	cout << endl;
}

//2、符号匹配（递归嵌套）
bool paren(const char exp[], int left, int right)
{//exp[left,right)
	Stack<char> S;//使用栈记录已发现但尚未匹配的左括号
	for (int i = left; i < right; i++)//逐一检查当前字符
	{
		if ('(' == exp[i])
		{
			S.push(exp[i]);//遇左括号：则进栈
		}
		else if (!S.empty())
		{
			S.pop();//遇右括号：若栈非空，则弹出左括号
		}
		else
		{
			return false;//否则（遇右括号时栈已空）必不匹配
		}
	}
	return S.empty();//最终，栈空当且仅当匹配
}
void test02()
{
	char c1[] = "(()())";
	
	bool e = paren(c1, 0, sizeof(c1)/sizeof(char)-1);
	if (e)
	{
		cout << "该字符串括号有序！" << endl;
	}
	else
	{
		cout << "该字符串括号无序" << endl;
	}
}

//栈混洗甄别
//禁形(312)





int main()
{
	//test01();//进制转换
	test02();//符号匹配

	return 0;
}