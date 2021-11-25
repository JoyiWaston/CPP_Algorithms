#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
    BitMap(size_t size = 100)            //���캯��
    {
        _v.resize((size >> 5) + 1);      //sizeΪҪ����ĵ�����������һ�����Ϳ��Դ��32������״̬����������vector��sizeΪsize/32
    }
    void Set(size_t x)                  //��xλ�õ�״̬��һ
    {
        if (x / 32 > _v.size())
        {
            cout << "����" << x << "������Χ" << endl;
            return;
        }
        size_t index = x >> 5;
        size_t num = x % 32;
        _v[index] |= 1 << (num - 1);
    }
    void Reset(size_t x)               //��xλ�õ�״̬������
    {
        if (x / 32 > _v.size())
        {
            cout << "����" << x << "������Χ" << endl;
            return;
        }
        size_t index = x >> 5;
        size_t num = x % 32;
        _v[index] ^= 1 << (num - 1);

    }

    int Find(size_t x)               //����xλ�õ�״̬������
    {
        if (x / 32 > _v.size())
        {
            cout << "����" << x << "������Χ" << endl;
            return false;
        }
        size_t index = x >> 5;
        size_t num = x % 32;
        return (_v[index] >> (num - 1)) & 1;
    }

private:
    vector<size_t>  _v;
};