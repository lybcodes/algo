#include <iostream>
using namespace std;

template<class T, int size = 0>
class Queue
{
public:
	Queue();
	bool isempty() const;
	bool isfull() const;

	void enqueue(const T&);
	T dequeue();

	void traverse() const;
private:
	T storge[size];
	int first;
	int last;
};

template<class T, int size>
Queue<T, size>::Queue()
{
	first = last = -1;
}

template<class T, int size>
bool Queue<T, size>::isempty()const
{
	return first == -1;
}

template<class T, int size>
bool Queue<T, size>::isfull()const
{
	return first == 0 && last == size - 1 || last == first - 1;
}

template<class T, int size>
void Queue<T, size>::enqueue(const T &elem)
{
	if (!isfull())
	{
		if (last == -1 || last == size - 1) //队列为空和到达队尾两种情况
		{
			storge[0] = elem;
			last = 0;
			if (first == -1)
				first = 0;
		}
		else storge[++last] = elem;
	}
	else
	{
		cout << "queue is full !" << endl;
	}
}

template<class T, int size>
T Queue<T, size>::dequeue()
{
	if (isempty())
		cout << "queue is empty" << endl;
	else
	{
		T tmp;
		tmp = storge[first];
		if (first == last)
			last = first = -1;
		else if (first == size - 1)
			first = 0;
		else ++first;
		return tmp;
	}
}

template<class T, int size>
void Queue<T, size>::traverse()const  //遍历
{
	if (first != -1)
	{
		for (auto i = first; i <= last; ++i)
			cout << storge[i] << " ";
		cout << endl;
	}
	else
		cout << "queue is empty !" << endl;
}


int main()
{
	Queue<int, 3> queue;
	queue.enqueue(10);
	queue.enqueue(11);
	queue.enqueue(12);

	queue.traverse();

	queue.dequeue();
	queue.dequeue();
	queue.dequeue();

	queue.isempty();
	queue.traverse();

	system("pause");
}