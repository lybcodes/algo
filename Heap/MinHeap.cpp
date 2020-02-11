/*小顶堆的实现*/

#include <iostream>
#include <assert.h>
#include "heap.h"

template<typename T>
class MinHeap : public Heap<T>
{
public:
	MinHeap(int);
	MinHeap(const T[], const int);
	~MinHeap();
public:
	bool insert_heap(const T&);
	bool remove_heap(T&);
	void shoe_heap()const;
protected:
	void sift_down(int, int);
	void sift_up(int);
private:
	T* heap;
	int size;
	int capacity;
};

template<typename T>
MinHeap<T>::MinHeap(int sz = DEFAULT_SIZE)
{
	capacity = sz > DEFAULT_SIZE ? sz : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = 0;
}

template<typename T>
MinHeap<T>::MinHeap(const T arr[], const int arrSize)
{
	capacity = arrSize > DEFAULT_SIZE ? arrSize : DEFAULT_SIZE;
	heap = new T[capacity];
	assert(heap != NULL);
	size = arrSize;

	for (int i = 0; i < size; ++i)
		heap[i] = arr[i];

	int curPos = size / 2 - 1;
	while (curPos >= 0)
	{
		sift_down(curPos, size - 1);
		--curPos;
	}
}

template<typename T>
MinHeap<T>::~MinHeap()
{
	delete[]heap;
	heap = NULL;
	capacity = size = 0;
}

template<typename T>
bool MinHeap<T>::insert_heap(const T& val)
{
	if (size >= capacity)
		return false;
	heap[size] = val;
	sift_up(size);
	++size;
	return true;
}

template<typename T>
bool MinHeap<T>::remove_heap(T& val)
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
void MinHeap<T>::shoe_heap()const
{
	for (int i = 0; i < size; ++i)
		cout << heap[i] << " ";
	cout << endl;
}

template<typename T>
void MinHeap<T>::sift_down(int start, int end)
{
	int i = start;
	int j = start * 2 + 1;

	T tmp = heap[i];
	while (j <= end)
	{
		if (j < end && heap[j] > heap[j + 1])
			++j;
		if (tmp < heap[j])
			break;
		else
			heap[i] = heap[j];

		i = j;
		j = j * 2 + 1;
	}
	heap[i] = tmp;
}

template<typename T>
void MinHeap<T>::sift_up(int start)
{
	int j = start;
	int i = (start - 1) / 2;

	T tmp = heap[j];
	while (j > 0)
	{
		if (tmp > heap[i])
			break;
		else
			heap[j] = heap[i];

		j = i;
		i = (i - 1) / 2;
	}
	heap[j] = tmp;
}