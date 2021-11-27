#include "Stack.hpp"

//1������ת�������������
void convert(Stack<char>& S, __int64 n, int base)
{
	static char digit[] = //�½����µ���λ���ţ�����Ϊbaseȡֵ��Χ�ʵ�����
	{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (n > 0)//�ɵ͵��ߣ���һ���㴦�½����µĸ���λ
	{
		S.push(digit[n % base]);//��������Ӧ��λ����ջ
		n /= base;//n����Ϊ���base�ĳ���
	}
}
void test01()
{
	int n = 10;
	int base = 3;

	Stack<char> S;
	convert(S, n, base);//��ջ��¼ת���õ���λ��
	while (!S.empty())
	{
		cout << S.pop() << " ";
	}
	cout << endl;
}

//2������ƥ�䣨�ݹ�Ƕ�ף�
bool paren(const char exp[], int left, int right)
{//exp[left,right)
	Stack<char> S;//ʹ��ջ��¼�ѷ��ֵ���δƥ���������
	for (int i = left; i < right; i++)//��һ��鵱ǰ�ַ�
	{
		if ('(' == exp[i])
		{
			S.push(exp[i]);//�������ţ����ջ
		}
		else if (!S.empty())
		{
			S.pop();//�������ţ���ջ�ǿգ��򵯳�������
		}
		else
		{
			return false;//������������ʱջ�ѿգ��ز�ƥ��
		}
	}
	return S.empty();//���գ�ջ�յ��ҽ���ƥ��
}
void test02()
{
	char c1[] = "(()())";
	
	bool e = paren(c1, 0, sizeof(c1)/sizeof(char)-1);
	if (e)
	{
		cout << "���ַ�����������" << endl;
	}
	else
	{
		cout << "���ַ�����������" << endl;
	}
}

//ջ��ϴ���
//����(312)





int main()
{
	//test01();//����ת��
	test02();//����ƥ��

	return 0;
}