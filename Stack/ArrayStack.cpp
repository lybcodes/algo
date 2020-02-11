#include <iostream>
using namespace std;

template<class T>
class arraystack
{
public:
	arraystack();
	~arraystack();
	bool isempty();
	void push(const T &data);
	void pop();
	T &gettop();

private:
	T *stacknodes;
	int top;
	int capacity;
};

template<class T>
arraystack<T>::arraystack()
{
	capacity = 3;
	stacknodes = new T[3];
	top = -1;
	cout << "the stack is constructed!" << endl;
	cout << "the capacity is :" << capacity << endl;
}

template<class T>
arraystack<T>::~arraystack()
{
	delete[]stacknodes;
	capacity = 0;
	top = -1;
	cout << "the stack is destoryed!" << endl;
}

template<class T>
bool arraystack<T>::isempty()
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class T>
void arraystack<T>::push(const T &data)  //压栈
{
	if (top + 1 == capacity)
	{
		capacity = 2 * capacity;
		T *p = new T[capacity];
		for (int i = 0; i <= top; i++)
			p[i] = stacknodes[i];
		T *q = stacknodes;
		stacknodes = p;
		delete[]q;
		cout << "the capacity is :" << capacity << endl;
	}
	stacknodes[++top] = data; //top初始值为-1，往里添加元素数组下标从0开始
	cout << "push in :" << stacknodes[top] << endl;
}

template<class T>
void arraystack<T>::pop()            //出栈
{
	if (!isempty())
		top--;
}

template<class T>
T &arraystack<T>::gettop()          //获取栈顶元素
{
	if (!isempty())
		return stacknodes[top];
}

#if 0
int main()
{
	const int n = 5;
	int data;
	arraystack<int> stk;       //定义类对象
	int a[n] = {4, 6, 8, 12, 9};
	for (int i = 0; i < n; i++)
		stk.push(a[i]);

	while (!stk.isempty())
	{
		data = stk.gettop();
		cout << "pop out :" << data << endl;
		stk.pop();
	}

	system("pause");
}
#endif