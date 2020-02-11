/*大顶堆的实现*/

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
MaxHeap<T>::MaxHeap(int sz = DEFAULT_SIZE)  //构造函数
{
	capacity = sz > DEFAULT_SIZE ? sz : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = 0;
}

template<typename T>
MaxHeap<T>::MaxHeap(const T arr[], const int arrSize) //构造函数
{
	capacity = arrSize > DEFAULT_SIZE ? arrSize : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = arrSize;

	for (int i = 0; i < size; ++i)
		heap[i] = arr[i];

	int curPos = size / 2 - 1; //父子节点
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

/*从上往下堆化，从某个节点开始分别与其左右孩子比较*/
template<typename T>
void MaxHeap<T>::sift_down(int start, int end)
{
	int i = start;	    //i节点
	int j = i * 2 + 1;  //i节点的左子节点

	T tmp = heap[i];
	while (j <= end)
	{
		if (j + 1 <= end && heap[j] < heap[j + 1]) //左子节点小于右子节点，j++，j现在就是右子节点（这一步就是找出左右子节点中最大的子节点 再与父节点比较，因为是大顶堆嘛）
			++j;
		if (tmp < heap[j])						   //父节点小于右子节点 交换（这一步并未交换元素完成）
			heap[i] = heap[j];
		else
			break;

		i = j;
		j = j * 2 + 1;
	}
	heap[i] = tmp;								  //这一步才交换完成
}

/*从下往上堆化，从某个元素x开始，如果其比父节点还大，
  那么就把父节点覆盖到x的位置上，然后假设x被放到父节点的位置，
  重复上面的过程，直到x大于或等于他的左右孩子
  或到达了堆顶，然后把x放到最新空出来的位置上*/
template<typename T>
void MaxHeap<T>::sift_up(int start)
{
	int j = start;
	int i = (start - 1) / 2; //j 的父节点

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
