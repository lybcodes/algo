/*�󶥶ѵ�ʵ��*/

#include <iostream>
#include <assert.h>
#include "heap.h"

template<typename T>
class MaxHeap :public Heap<T>
{
public:
	MaxHeap(int);
	MaxHeap(const T[], const int);
	~MaxHeap();
public:
	bool insert_heap(const T&);
	bool remove_heap(T&);
	void show_heap()const;
protected:
	void sift_down(int, int);
	void sift_up(int);
private:
	T *heap;
	int size;
	int capacity;
};

template<typename T>
MaxHeap<T>::MaxHeap(int sz = DEFAULT_SIZE)  //���캯��
{
	capacity = sz > DEFAULT_SIZE ? sz : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = 0;
}

template<typename T>
MaxHeap<T>::MaxHeap(const T arr[], const int arrSize) //���캯��
{
	capacity = arrSize > DEFAULT_SIZE ? arrSize : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = arrSize;

	for (int i = 0; i < size; ++i)
		heap[i] = arr[i];

	int curPos = size / 2 - 1; //���ӽڵ�
	while (curPos >= 0)
	{
		sift_down(curPos, size - 1);
		--curPos;
	}
}

template<typename T>
MaxHeap<T>::~MaxHeap()
{
	delete[]heap;
	heap = NULL;
	capacity = size = 0;
}

template<typename T>
bool MaxHeap<T>::insert_heap(const T& val)
{
	if (size >= capacity)
		return false;

	heap[size] = val;
	sift_up[size];
	++size;
	return true;
}

template<typename T>
bool MaxHeap<T>::remove_heap(T& val)
{
	if (size <= 0)
		return false;

	val = heap[0];
	heap[0] = heap[size - 1];
	--size;
	sift_down(0, size - 1);
	return true;
}

template<typename T>
void MaxHeap<T>::show_heap()const
{
	for (int i = 0; i < size; ++i)
		cout << heap[i] << " ";
	cout << endl;
}

/*�������¶ѻ�����ĳ���ڵ㿪ʼ�ֱ��������Һ��ӱȽ�*/
template<typename T>
void MaxHeap<T>::sift_down(int start, int end)
{
	int i = start;	    //i�ڵ�
	int j = i * 2 + 1;  //i�ڵ�����ӽڵ�

	T tmp = heap[i];
	while (j <= end)
	{
		if (j + 1 <= end && heap[j] < heap[j + 1]) //���ӽڵ�С�����ӽڵ㣬j++��j���ھ������ӽڵ㣨��һ�������ҳ������ӽڵ��������ӽڵ� ���븸�ڵ�Ƚϣ���Ϊ�Ǵ󶥶��
			++j;
		if (tmp < heap[j])						   //���ڵ�С�����ӽڵ� ��������һ����δ����Ԫ����ɣ�
			heap[i] = heap[j];
		else
			break;

		i = j;
		j = j * 2 + 1;
	}
	heap[i] = tmp;								  //��һ���Ž������
}

/*�������϶ѻ�����ĳ��Ԫ��x��ʼ�������ȸ��ڵ㻹��
  ��ô�ͰѸ��ڵ㸲�ǵ�x��λ���ϣ�Ȼ�����x���ŵ����ڵ��λ�ã�
  �ظ�����Ĺ��̣�ֱ��x���ڻ�����������Һ���
  �򵽴��˶Ѷ���Ȼ���x�ŵ����¿ճ�����λ����*/
template<typename T>
void MaxHeap<T>::sift_up(int start)
{
	int j = start;
	int i = (start - 1) / 2; //j �ĸ��ڵ�

	T tmp = heap[j];
	while (j > 0)
	{
		if (tmp < heap[i])
			break;
		else
			heap[j] = heap[i];

		j = i;
		i = (i - 1) / 2;
	}
	heap[j] = tmp;
}
