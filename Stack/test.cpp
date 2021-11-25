#include "Stack.hpp"

void convert(Stack<char>& S, __int64 n, int base)
{
	static char digit[] = //�½����µ���λ���ţ�����Ϊbaseȡֵ��Χ�ʵ�����
	{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (n > 0)//�ɵ͵��ߣ���һ���㴦�½����µĸ���λ
	{
		S.push(digit[n & base]);//��������Ӧ��λ����ջ
		n /= base;//n����Ϊ���base�ĳ���
	}
}

int main()
{
	Stack<char> S;
	convert(S, n, base);//��ջ��¼ת���õ���λ��
	while (!S.empty())
	{
		cout << S.pop() << " ";
	}
	cout << endl;
}