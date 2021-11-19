#pragma once
#include "Vector_Include.h"

using Rank = int;// ��
const int DEFAULT_CAPACITY = 3;// Ĭ�ϳ�ʼ������ʵ��Ӧ�ù����п������ø���

template <class T>
class Vector
{
	// ����ģ����
private:
	Rank _size;			// ��ģ
	int _capacity;		// ����
	T* _elem;			// ������

protected:
	Rank _size; int _capacity;  T* _elem; //��ģ��������������

	void copyFrom(T const* A, Rank left, Rank right); //������������A[lo, hi)

	void expand(); //�ռ䲻��ʱ����

	void shrink(); //װ�����ӹ�Сʱѹ��

	bool bubble(Rank left, Rank right); //ɨ�轻��

	void bubbleSort(Rank left, Rank right); //���������㷨

	Rank maxItem(Rank left, Rank right); //ѡȡ���Ԫ��

	void selectionSort(Rank left, Rank right); //ѡ�������㷨

	void merge(Rank left, Rank middle, Rank right); //�鲢�㷨

	void mergeSort(Rank left, Rank right); //�鲢�����㷨

	void heapSort(Rank left, Rank right); //�������Ժ�����ȫ�ѽ��⣩

	Rank partition(Rank left, Rank right); //��㹹���㷨

	void quickSort(Rank left, Rank right); //���������㷨

	void shellSort(Rank left, Rank right); //ϣ�������㷨

public:
	// ���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)// ����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const* A, Rank n)//�������帴��
	{
		copyFrom(A, 0, n);
	}

	Vector(T const* A, Rank left, Rank right)//�������临��
	{
		copyFrom(A, left, right);
	}

	Vector(Vector<T> const& V)//�������帴��
	{
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank left, Rank right)//�������临��
	{
		copyFrom(V._elem, left, right);
	}

	// ��������
	~Vector()
	{
		delete[] _elem;//�ͷ��ڲ��ռ�
	}

	// ֻ���ӿ�
	Rank size() const { return _size; }//��ģ

	bool empty() const { return !_size; }//�п�

	int disordered() const;//�ж��Ƿ�����ͳ�������

	Rank find(T const& e) const { return find(e, 0, _size); }//���������������

	Rank find(T const& e, Rank left, Rank right) const;//���������������
	
	Rank search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }//���������������

	Rank search(T const& e, Rank left, Rank right) const;//���������������

	// ��д�ӿ�
	T& operator[](Rank r) const { return _elem[r]; }//�����±������������������������ʽ���ø�Ԫ��

	const T& operator[](Rank r) const { return _elem[r]; };//��������ֵ�����ذ汾

	Vector<T>& operator=(Vector<T> const&);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����

	T remove(Rank r);//ɾ����Ϊr��Ԫ��

	int remove(Rank left, Rank right);//ɾ����������[left,right)֮�ڵ�Ԫ��

	Rank insert(Rank r, T const& e);//����Ԫ��

	Rank insert(T const& e) { return insert(_size, e); }//Ĭ����ΪĩԪ�ز���

	void sort(Rank left, Rank right); //��[lo, hi)����

	void sort() { sort(0, _size); } //��������

	void unsort(Rank left, Rank right); //��[lo, hi)����

	void unsort() { unsort(0, _size); } //��������

	int deduplicate(); //����ȥ��

	int uniquify(); //����ȥ��


	// �����ӿ�
	void traverse(void(*)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ��޸ģ�
	
	template<typename VST>
	void traverse(VST&);//������ʹ�ú������󣬿�ȫ�����޸ģ�

};