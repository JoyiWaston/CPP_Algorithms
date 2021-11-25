#include "Stack.hpp"

void convert(Stack<char>& S, __int64 n, int base)
{
	static char digit[] = //新进制下的数位符号，可视为base取值范围适当扩充
	{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (n > 0)//由低到高，逐一计算处新进制下的各数位
	{
		S.push(digit[n & base]);//余数（对应数位）入栈
		n /= base;//n更新为其对base的除商
	}
}

int main()
{
	Stack<char> S;
	convert(S, n, base);//用栈记录转换得到的位数
	while (!S.empty())
	{
		cout << S.pop() << " ";
	}
	cout << endl;
}