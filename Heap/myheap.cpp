#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

/*建堆*/
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

template<typename T, typename compare=MaxHeap<T>> //默认构建大顶堆
class Heap
{
public:
	Heap() = default;

	Heap(const T* a, int size)
	{
		assert(a);
		_a.reserve(size); //vector中的方法 知道存放的元素个数可先预留空间，一次完成拷贝，节省申请释放内存的次数，节省时间
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int i = size / 2 - 1; i >= 0; i--) //从第一个非叶子节点开始调整 //这里i必须是int 否则程序死循环
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
	void  sift_down(int root) //自上而下调整
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

	void sift_up(int child) //自下而上调整
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


//测试
void test_heap()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int> heap(a, sizeof(a) / sizeof(a[0]));
	heap.insert(20);
	heap.remove();
}



/*====================================优先级队列================================*/
//默认大顶堆
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

//测试
void test_PriorityQueue()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	PriorityQueue<int>q(a, 10);
	q.push(100);
	q.pop();
	int b = q.top();
	cout << b << endl;
}

/*====================================堆排序================================*/
//升序大顶堆  降序小顶堆
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

	for (int i = n / 2 - 1; i >= 0; --i) //建堆
	{
		sift_down(a, n, i);
	}
	int end = n - 1;
	for (int i = 0; i < n; ++i)
	{
		swap(a[0], a[end]); //交换大顶堆中堆顶元素和最后一个元素，数组中最后一个元素即为最大
		sift_down(a, end, 0); //调整堆
		--end;
	}
}
//测试
void test_heap_sort()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	heap_sort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i] << " ";
}


/*====================================Top K问题======================================*/
//找出数组中最大的前K个数 使用小顶堆实现
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
			//先将数组的前K个数放入堆中
			if (i < k)
				_h.insert(a[i]);
			else
			{
				//如果接下来的元素比Top元素大 删除Top元素 插入该元素
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
//测试
void test_TopK()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	TopK<int> top(a, sizeof(a) / sizeof(a[0]), 5);
}


