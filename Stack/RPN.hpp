#pragma once
//3���ӳٻ��壨��׺���ʽ��
//��ֵ�㷨 = ջ + ����ɨ��
#include <iostream>
#include "Stack.hpp"

using namespace std;


#define N_OPTR 9 //���������
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
   /*              |-------------------- �� ǰ �� �� �� --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

void readNumber(char*& p, Stack<double>& stk)
{
	//����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
	stk.push((double)(*p - '0')); //��ǰ��λ��Ӧ����ֵ��ջ
	while (isdigit(*(++p))) //ֻҪ�������н��ڵ����֣�����λ���������������
	{
		stk.push(stk.pop() * 10 + (*p - '0')); //����ԭ��������׷������λ������ֵ������ջ
	}

	if ('.' != *p) return; //�˺��С���㣬����ζ�ŵ�ǰ�������������

	float fraction = 1; //������ζ�Ż���С������
	while (isdigit(*(++p))) //��λ����
	{
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //С������
	}
}

void append(char*& rpn, double opnd)
{
	//������������RPNĩβ
	char buf[64];
	if (0.0 < opnd - (int)opnd)
	{
		//printf(buf, "%f \0", opnd); //�����ʽ����
		cout << buf << (float)opnd << '\0' << endl;
	}
	else
	{
		//sprintf(buf, "%d \0", (int)opnd); //������ʽ
		cout << buf << (int)opnd << '\0' << endl;
	}
	rpn = (char*)realloc(rpn, sizeof(char) * (strlen(rpn) + strlen(buf) + 1)); //��չ�ռ�
	strcat(rpn, buf); //RPN�ӳ�
}

void append(char*& rpn, char optr)
{
	//�����������RPNĩβ
	int n = strlen(rpn); //RPN��ǰ���ȣ���'\0'��β������n + 1��
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); //��չ�ռ�
	sprintf(rpn + n, "%c ", optr); rpn[n + 2] = '\0'; //����ָ���������
}


Operator optr2rank(char op) { //�������ת������
	switch (op) {
	case '+': return ADD; //��
	case '-': return SUB; //��
	case '*': return MUL; //��
	case '/': return DIV; //��
	case '^': return POW; //�˷�
	case '!': return FAC; //�׳�
	case '(': return L_P; //������
	case ')': return R_P; //������
	case '\0': return EOE; //��ʼ������ֹ��
	default: exit(-1); //δ֪�����
	}
}

char orderBetween(char op1, char op2) //�Ƚ����������֮������ȼ�
{
	return pri[optr2rank(op1)][optr2rank(op2)];
}

double calcu(double a, char op, double b) { //ִ�ж�Ԫ����
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': if (0 == b) exit(-1); return a / b; //ע�⣺����и�����Ϊ����ܲ���ȫ
	case '^': return pow(a, b);
	default: exit(-1);
	}
}

__int64 facI(int n) { __int64 f = 1; while (n > 1) f *= n--; return f; } //�׳����㣨�����棩

double calcu(char op, double b) { //ִ��һԪ����
	switch (op) {
	case '!': return (double)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
	default: exit(-1);
	}
}

double evaluate(char* S, char*& RPN)//��׺���ʽ��ֵ
{
	Stack<double> opnd; Stack<char> optr;//������ջ�������ջ
	char* expr = S;
	optr.push('\0');//β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
	while (!optr.empty())//��������ַ���ֱ�������ջΪ��
	{
		if (isdigit(*S))//����ǰ�ַ�Ϊ������
		{
			readNumber(S, opnd);//���루���ܶ�λ��������
			append(RPN, opnd.top());//����RPNĩβ
		}
		else//����ǰ�ַ�Ϊ���������������ջ�������֮������ȼ��ĸߵ� �ֱ���
		{
			switch (orderBetween(optr.top(), *S))
			{
			case '<': //ջ����������ȼ�����ʱ
				optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ
				break;

			case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
				optr.pop(); S++; //�����Ų�������һ���ַ�
				break;

			case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop(); append(RPN, op); //ջ���������ջ��������RPNĩβ
				if ('!' == op)
				{ //������һԪ�����
					double pOpnd = opnd.pop(); //ֻ��ȡ��һ������������
					opnd.push(calcu(op, pOpnd)); //ʵʩһԪ���㣬�����ջ
				}
				else
				{ //������������Ԫ�������
					double pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //ȡ����ǰ������ /*DSA*/���ʣ��ɷ�ʡȥ������ʱ������
					opnd.push(calcu(pOpnd1, op, pOpnd2)); //ʵʩ��Ԫ���㣬�����ջ
				}
				break;
			}
			default: exit(-1); //���﷨���󣬲�������ֱ���˳�
			}
		}
	}
	return opnd.pop();//�������������ļ�����
}