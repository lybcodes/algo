#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

/*����*/
template <typename T>
struct MinHeap
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template<typename T>
struct MaxHeap
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<typename T, typename compare=MaxHeap<T>> //Ĭ�Ϲ����󶥶�
class Heap
{
public:
	Heap() = default;

	Heap(const T* a, int size)
	{
		assert(a);
		_a.reserve(size); //vector�еķ��� ֪����ŵ�Ԫ�ظ�������Ԥ���ռ䣬һ����ɿ�������ʡ�����ͷ��ڴ�Ĵ�������ʡʱ��
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int i = size / 2 - 1; i >= 0; i--) //�ӵ�һ����Ҷ�ӽڵ㿪ʼ���� //����i������int ���������ѭ��
		{
			sift_down(i);
		}
		//for (int i = 0; i < size; i++)
		//{
		//	cout << _a[i] << " ";
		//}
		//cout << endl;
	}

	void insert(const T& n) //
	{
		_a.push_back(n);
		int child = _a.size() - 1;
		sift_up(child);
		//for (int i = 0; i < _a.size(); i++)
		//{
		//	cout << _a[i] << " ";
		//}
		//cout << endl;
	}

	void remove()
	{
		assert(!_a.empty());
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		sift_down(0);
		//for (int i = 0; i < _a.size(); i++)
		//{
		//	cout << _a[i] << " ";
		//}
		//cout << endl;
	}

	int size()
	{
		return _a.size();
	}

	const T& top()
	{
		return _a[0];
	}

protected:
	void  sift_down(int root) //���϶��µ���
	{
		int child = root * 2 + 1;
		while (child < _a.size())
		{
			compare comp;
			if ((child + 1) < _a.size() && comp(_a[child + 1], _a[child]))
				++child;
			if (comp(_a[child], _a[root]))
			{
				swap(_a[child], _a[root]);
				root = child;
				child = root * 2 + 1;
			}
			else
				break;
		}
	}

	void sift_up(int child) //���¶��ϵ���
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			compare comp;
			if (comp(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

public:
	vector<T> _a;
};


//����
void test_heap()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int> heap(a, sizeof(a) / sizeof(a[0]));
	heap.insert(20);
	heap.remove();
}



/*====================================���ȼ�����================================*/
//Ĭ�ϴ󶥶�
template<typename T, typename compare=MaxHeap<T>>
class PriorityQueue
{
public:
	PriorityQueue() = default;

	PriorityQueue(T* a, int n)
	{
		for (int i = 0; i < n; i++)
		{
			_h.insert(a[i]);
		}
	}

	void push(const T& x)
	{
		_h.insert(x);
	}
	void pop()
	{
		_h.remove();
	}
	int size()
	{
		return _h.size();
	}
	const T& top()
	{
		return _h.top();
	}

protected:
	Heap<T, compare>_h;
};

//����
void test_PriorityQueue()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	PriorityQueue<int>q(a, 10);
	q.push(100);
	q.pop();
	int b = q.top();
	cout << b << endl;
}

/*====================================������================================*/
//����󶥶�  ����С����
void sift_down(int a[], int n, int root)
{
	if (a == NULL)
		return;

	int parent = root;
	int child = parent * 2 + 1;

	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
			++child;
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
			break;
	}
}

void heap_sort(int a[], int n)
{
	if (a == NULL)
		return;

	for (int i = n / 2 - 1; i >= 0; --i) //����
	{
		sift_down(a, n, i);
	}
	int end = n - 1;
	for (int i = 0; i < n; ++i)
	{
		swap(a[0], a[end]); //�����󶥶��жѶ�Ԫ�غ����һ��Ԫ�أ����������һ��Ԫ�ؼ�Ϊ���
		sift_down(a, end, 0); //������
		--end;
	}
}
//����
void test_heap_sort()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	heap_sort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i] << " ";
}


/*====================================Top K����======================================*/
//�ҳ�����������ǰK���� ʹ��С����ʵ��
template<typename T, typename compare=MinHeap<T>>
class TopK
{
public:
	TopK() = default;

	TopK(int *a, int n, int k)
	{
		assert(k <= n);
		int i = 0;
		while (i < n)
		{
			//�Ƚ������ǰK�����������
			if (i < k)
				_h.insert(a[i]);
			else
			{
				//�����������Ԫ�ر�TopԪ�ش� ɾ��TopԪ�� �����Ԫ��
				if (a[i] > _h.top())
				{
					_h.remove();
					_h.insert(a[i]);
				}
			}
			++i;
		}
		for (int i = 0; i < 5; ++i)
		{
			cout << _h._a[i] << " ";
		}
	}
protected:
	Heap<T, compare> _h;
};
//����
void test_TopK()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	TopK<int> top(a, sizeof(a) / sizeof(a[0]), 5);
}


