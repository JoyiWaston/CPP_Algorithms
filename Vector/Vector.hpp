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
	//Rank _size; int _capacity;  T* _elem; //��ģ��������������

	void copyFrom(T const* A, Rank left, Rank right); //������������A[lo, hi)

	void expand(); //�ռ䲻��ʱ����

	void shrink(); //װ�����ӹ�Сʱѹ��

	//bool bubble(Rank left, Rank right); //ɨ�轻��
	//�Ľ�Ϊ��
	Rank bubble(Rank left, Rank right); //ɨ�轻��

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

	//const T& operator[](Rank r) const { return _elem[r]; }//��������ֵ�����ذ汾

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

template <typename T> 
Vector<T>& Vector<T>::operator= (Vector<T> const& V) 
{ 
	//���
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}


template <typename T>//TΪ�������ͣ��������ظ�ֵ������"="
void Vector<T>::copyFrom(T const* A, Rank left, Rank right)
{
	_elem = new T[_capacity = 2 * (right - left)];//����ռ�
	//��ģ����
	for (_size = 0; left < right; _size++, left++)//A[left,right)��Ԫ����һ���
	{
		_elem[_size] = A[left];//������ _elem[0,right-left)
	}
}
//����ʱ�� = O(right-left)


//����
template <typename T>
void Vector<T>::expand()//�����ռ䲻��ʱ����
{
	if (_size < _capacity)
	{
		return;
	}

	_capacity = max(_capacity, DEFAULT_CAPACITY);//��������С����

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//�����ӱ�		���μ���O��n����		�̶���ֵ����	��������O(n^2) ;
	for (int i = 0; i < _size; i++)//����ԭ��������
	{
		_elem[i] = oldElem[i];	   //TΪ�������ͣ��������ظ�ֵ������'='
	}

	delete[] oldElem;//�ͷ�ԭ�ռ�
}

//����
template <typename T>
void Vector<T>::shrink()
{
	//װ�����ӹ�Сʱѹ��������ռ�ռ�
	if (_capacity < DEFAULT_CAPACITY << 1)
	{
		return; //����������DEFAULT_CAPACITY����
	}

	if (_size << 2 > _capacity)
	{
		return; //��25%Ϊ��
	}

	T* oldElem = _elem;  //ԭ�����ݱ���
	_elem = new T[_capacity >>= 1]; //��������

	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //����ԭ��������
	}

	delete[] oldElem; //�ͷ�ԭ�ռ�
}


//Ψһ�����㷨
//Ӧ��ʵ������������ �ľֲ��������ȥ�ز���������Ϊ���ձ���

// ������
//template <typename T>
//int Vector<T>::deduplicate()
//{
//	int oldSize = _size;//��¼ԭ��ģ
//	Rank i = 1;//��_elem[1]��ʼ
//
//	while (i < _size)//��ǰ���ע�⿼���Ԫ��_elem[i]
//	{
//		//��ǰ׺��Ѱ����ͬ��
//		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);//������ͬ�����������
//		//����ɾ����ͬ(����ֻ��һ����ֵͬ��)
//	}
//	return oldSize - _size;//������ģ�仯�ˣ���ɾ��Ԫ������
//}
//ɾ�������������ظ�Ԫ�أ���Ч�棩
template <typename T>
int Vector<T>::deduplicate()
{

	int oldSize = _size; //��¼ԭ��ģ
	Rank i = 1; //��_elem[1]��ʼ

	while (i < _size) //��ǰ�����һ�����Ԫ��_elem[i]
	{
		if (find(_elem[i], 0, i) < 0) //��ǰ׺[0,i)��Ѱ����֮��ͬ�ߣ�����һ����
		{
			i++; //������ͬ�������������
		}
		else
		{
			remove(i); //����ɾ����ǰԪ��
		}
	}
	return oldSize - _size; //��ɾ��Ԫ������
}

template <typename T>
int Vector<T>::disordered() const
{
	int count = 0;//������
	for (int i = 1; i < _size; i++)//��һ����������Ԫ��
	{
		count += (_elem[i - 1] > _elem[i]);//���������
	}
	return count;//���������ҽ���n = 0
}//��ֻ���ж��Ƿ��������״����������֮�󼴿���ֹ


//��Ч�㷨		O(n^2)
//ԭ�򣺵�Ч�ĸ�Դ���ڣ�ͬһԪ�ؿ���Ϊ��ɾ��Ԫ�صĺ�̶��ǰ��
//��ʾ���������ظ�����Ϊ��λ������ɾ����ͬԪ�أ����ܱؽ��Ľ�
//template<typename T>
//int Vector<T>::uniquify()
//{
//	int oldSize = _size;
//	int i = 0;					//����Ԫ�ؿ�ʼ
//
//	while (i < _size - 1)		//��ǰ�����һ�ȶԸ�������Ԫ�أ���ͬ��ɾ�����ߣ�����ת����һ��Ԫ��
//	{
//		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;
//	}
//	return oldSize = _size;//������ģ�仯������ɾ��Ԫ������
//}//ע�⣺����_size�ļ�С����remove()��ʽ�����

//��Ч��
template<typename T>
int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;//���Ի���"����"Ԫ�ص���
	while (++j < _size)//��һɨ�裬ֱ��ĩԪ��
	//������ͬ�ߣ����ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();//ֱ�ӽس�β������Ԫ��

	return j - i;//������ģ�仯��������ɾ��Ԫ������
}//ע�⣺ͨ��remove(left,right)����ɾ������Ȼ���ܴﵽ��Ч��


//����Ԫ��
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)		//O(n-r)
{
	expand();//���б�Ҫ������
	for (int i = _size; i > r; i--)//�Ժ���ǰ
	{
		_elem[i] = _elem[i - 1];//���Ԫ��˳�κ���һ����Ԫ
	}
	_elem[r] = e;//������Ԫ��
	_size++;//��������

	return r;//������
}

//ɾ��Ԫ��
template <typename T>
int Vector<T>::remove(Rank left, Rank right)		//O(n-right)
{
	if (left == right)
	{
		return 0;//����Ч�ʿ��ǣ����������˻����
	}

	while (right < _size)
	{
		_elem[left++] = _elem[right++];// [right��_size) ˳��ǰ�� right-left λ
	}
	_size = left;//���¹�ģ
	shrink();//���б�Ҫ������

	return right - left;//���ر�ɾ��Ԫ�ص���Ŀ
}

template <typename T>
T Vector<T>::remove(Rank r)
{
	//ɾ����������Ϊr��Ԫ�أ�0 <= r < size
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}


//����������TΪ�� �е� �Ļ������ͣ��������ز����� == �� !=
//����������TΪ�� �Ƚ� �Ļ������ͣ��������ز����� <  �� >
//������������
template <typename T>
Rank Vector<T>::find(T const& e, Rank left, Rank right) const
//O(right - left) = O(n)   �����ж��Ԫ��ʱ�ɷ��� �������
{
	while ((left < right--) && (e != _elem[right]));	//�������

	return right;//right < left ��ζ��ʧ�ܣ�����right������Ԫ�ص���
}// Excel::match(e, range, type);

// �����㷨Ϊ ��������(input-sensitive)�㷨��������O(1),����O(n)


//�����ӿ�
//���ú���ָ����ƣ�ֻ���� �ֲ��� �޸�
template <typename T>
void Vector<T>::traverse(void (*visit)(T&))//����ָ��
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//���ú���������ƣ��� ȫ�����޸�
template <typename T>	template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}


//// �������������ֲ���A
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank left, Rank right)
//{
//	while (left < right)
//	{
//		Rank middle = (left + right) >> 1;//���е�Ϊ���
//
//		if (e < A[middle])//����ǰ���[left,middle)
//		{
//			right = middle;
//		}
//		else if (A[middle] < e)//������Σ�middle,right��
//		{
//			left = middle + 1;
//		}
//		else//��middle���ҵ���Ԫ��
//		{
//			cout << "ʹ���˶��ֲ���!" << endl;
//			return middle;
//		}
//	}
//	cout << "ʹ���˶��ֲ���A!" << endl;
//	return -1;//����ʧ��
//}

////���ֲ���B
////���ж������Ԫ�أ����뷵��������Ԫ��
////ʧ��ʱӦ�÷���С��Ŀ�������ߣ���[left-1]��
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank left, Rank right)
//{
//	while (1 < right - left)//��Ч����������������1���㷨��ֹ
//	{
//		Rank middle = (left + right) >> 1;//�е���Ϊ��㣬�����ȽϺ�ȷ������
//
//		(e < A[middle]) ? right = middle : left = middle;//���������
//	}//��whileʱ��right = left + 1�������������һ��Ԫ��A[left]
//	cout << "ʹ���˶��ֲ���B!" << endl;
//	return (e == A[left]) > left : -1;//��������Ԫ�ص��� �����ʧ��
//}

//���ֲ���C
template <typename T>
static Rank binSearch(T* A, T const& e, Rank left, Rank right)
{
	while (left < right)//�����ԣ�A[0,left] <= e < A[right,n)	A[right]���Ǵ���Ŀ��Ԫ�ص���С��
	{
		Rank middle = (left + right) >> 1;//�е���Ϊ��㣬�����ȽϺ�ȷ������
		
		(e < A[middle]) ? right = middle : left = middle + 1;//�������
	}//��whileʱ��A[left = right]Ϊ����Ŀ��Ԫ�ص���СԪ��
	cout << "ʹ���˶��ֲ���C!" << endl;
	return --left;//��left-1��������Ŀ��Ԫ�ص������
}

//�Ľ��棨fibonacci��
//��n = fib(k) - 1,�����ȡmiddle = fib(k - 1) - 1;
//���ǣ�ǰ�����������ȷֱ�Ϊfib(k - 1) - 1��fib(k - 2) - 1;
template <typename T>
static Rank fibSearch(T* A, T const& e, Rank left, Rank right)
{
	Fib fib(right - left);//����Fibonacci����
	while (left < right)
	{
		while (right - left < fib.get())
		{
			fib.prev();
		}
		Rank middle = left + fib.get() - 1;//�ƽ�����з�
		if (e < A[middle])
		{
			right = middle;
		}
		else if (A[middle] < e)
		{
			left = middle + 1;
		}
		else
		{
			cout << "ʹ����fibonacci����!" << endl;
			return middle;
		}
	}
	cout << "ʹ����fibonacci����!" << endl;
	return -1;
}

// �����㷨ͳһ�ӿ�	0 <= left < right <= _size
template <typename T>
Rank Vector<T>::search(T const& e, Rank left, Rank right) const
{
	srand((unsigned int)time(NULL));
	return (rand() % 2) ?//�����ٷ�֮��ʮ�������ȡ��
		binSearch(_elem, e, left, right)//���ֲ����㷨
		: fibSearch(_elem, e, left, right);//Fibonacci�����㷨
}
//��δ������������
//���磬Ŀ��Ԫ�ز�����; ��Ŀ��Ԫ��ͬʱ���ڶ����

//����Լ����
//���٣�Ӧ�ñ����������������ά����V.insert(1 + V.search(e),e)
//��ʹʧ�ܣ�ҲӦ�ø�����Ԫ���ʵ������λ��
//�������ظ�Ԫ�أ���ÿһ��Ҳ�谴�����Ĵ�������

//Լ����
//��������������V[left,right)�У�ȷ��������e�����һ��Ԫ��
//�� -�� < e <V[left],�򷵻�left-1
//�� V[right - 1] < e < +�ޣ��򷵻�right-1


//BubbleSort	O(n^2)

// ��ʼ��
//template <typename T>
//bool Vector<T>::bubble(Rank left, Rank right)
//{
//	bool sorted = true;//���������־
//	while (++left < right)//�������ң���һ����������Ԫ��
//	{
//		if (_elem[left - 1] > _elem[left])//��������
//		{
//			sorted = false;
//			swap(_elem[left - 1], _elem[left]);//����
//		}
//	}
//	return sorted;//�����Ƿ������־
//}
// 
//template <typename T>
//void Vector<T>::bubbleSort(Rank left, Rank right)
//{
//	while (!bubble(left, right--));//������ɨ�轻����ֱ��ȫ��
//}

// �Ľ���
template <typename T>
Rank Vector<T>::bubble(Rank left, Rank right)
{
	Rank last = left;//���Ҳ������Գ�ʼ��Ϊ[left-1��left]
	while (++left < right)//�������ң���һ����������Ԫ��
	{
		if (_elem[left - 1] > _elem[left])//��������
		{
			
			last = left;//�������Ҳ������λ�ü�¼
			swap(_elem[left - 1], _elem[left]);//����
		}
	}
	return last;//�������Ҳ������λ��
}
template <typename T>
void Vector<T>::bubbleSort(Rank left, Rank right)
{
	while (left < (right = bubble(left, right)));
}


//MergeSort	O(nlogn)
template <typename T>
void Vector<T>::merge(Rank left, Rank middle, Rank right)
{
	T* A = _elem + left;//�ϲ�������� A[0,right - left) = _elem[left,right)   ��ţ�

	int ml = middle - left;
	T* B = new T[ml];//ǰ������B[0,lm) = _elem[left,middle)

	for (Rank i = 0; i < ml; B[i] = A[i++]);//����ǰ������B

	int rm = right - middle;
	T* C = _elem + middle;//��������C[0,rm) = _elem[middle,right)

	for (Rank i = 0, j = 0, k = 0; (j < ml)/* || (k < rm)*/;)//B[j]��C[k]�е�С��ת��A��ĩβ
	{
		if (/*(j < ml) && */(rm <= k || (B[j] <= C[k])))//C[k]���޻�С��B[j]
		{
			A[i++] = B[j++];
		}
		if ((k < rm) && (/*ml <= j || */(B[j] > C[k])))//C[k]���޻�С��B[j]
		{
			A[i++] = C[k++];
		}
	}
	delete[] B;
}


template <typename T>
void Vector<T>::mergeSort(Rank left, Rank right)
{
	if (right - left < 2) return;//��Ԫ�����䱾����Ȼ���򣬴���ݹ��
	int middle = (left + right) >> 1;//���е�Ϊ��

	mergeSort(left, middle);//��ǰ��εݹ�����
	mergeSort(middle, right);//�Ժ��εݹ�����
	merge(left, middle, right);//�鲢
}




template <typename T> 
void Vector<T>::sort(Rank left, Rank rigth) 
{ //��������[left, right)����
	//srand((unsigned int)time(NULL));
	//switch (rand()%6) 
	//{
	//	case 1:  bubbleSort(left, rigth); break; //��������
	//	case 2:  selectionSort(left, rigth); break; //ѡ������
	//	case 3:  mergeSort(left, rigth); break; //�鲢����
	//	case 4:  heapSort(left, rigth); break; //������
	//	case 5:  quickSort(left, rigth); break; //��������
	//	default: shellSort(left, rigth); break; //ϣ������
	//}

}