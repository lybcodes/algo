#include <iostream>
using namespace std;

template<class T>
struct linknode
{
	T data;
	linknode *next;
};

template<class T>
class mystack
{
public:
	mystack();
	~mystack();
	bool isempty();
	void push(const T &data);
	void pop();
	T &gettop();

private:
	linknode<T> *head;
	linknode<T> *top;
	int length;
};

template<class T>
mystack<T>::mystack()
{
	head = NULL;
	top = NULL;
	length = 0;
	cout << "the stack is constructed!" << endl;
}

template<class T>
mystack<T>::~mystack()
{
	while (!isempty())
		pop();
	cout << "the stack is destoryed!" << endl;
}

template<class T>
bool mystack<T>::isempty()
{
	if (head == NULL)
		return true;
	else
		return false;
}

template<class T>
void mystack<T>::push(const T &data)
{
	if (!head)  //头结点为空
	{
		head = new linknode<T>;
		head->data = data;
		head->next = NULL;
		top = head;
		length++;
		cout << "push in :" << top->data << endl;
	}
	else
	{
		linknode<T> *p = new linknode<T>;
		p->data = data;
		p->next = NULL;
		top->next = p;
		top = p;
		length++;
		cout << "push in :" << top->data << endl;
	}
}

template<class T>
void mystack<T>::pop()
{
	if (!isempty())
	{
		linknode<T> *p = head;
		if (p == top)
		{
			head = NULL;
			top = NULL;
		}
		else
		{
			while (p->next != top)
			{
				p = p->next;
			}
			top = p;
			p = top->next;
		}
		delete p;
		length--;
	}
}

template<class T>
T &mystack<T>::gettop()
{
	if (!isempty())
		return top->data;
}


#if 0
int main()
{
	const int n = 5;
	int data;
	mystack<int>stk;
	int a[n] = { 4, 5, 3, 8, 12 };
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