#include <iostream>

using namespace std;

//实现一个支持动态扩容的数组，动态的增删改查
const int initialLen = 10;
template<class T>
class Array
{
public:
	Array(int len = initialLen)
	{
		T *p = new T[len];
		m_data = p;
		m_capacity = len;
		m_size = 0;
	}
	int capacity()
	{
		return m_capacity;
	}
	int size()
	{
		return m_size;
	}
	void resize(int len)  //动态扩容
	{
		T *p = new T[len];
		for (int i = 0; i < m_size; i++)
		{
			p[i] = m_data[i];
		}
		delete[] m_data;
		m_data = p;
		m_capacity = len;
	}
	bool isEmpty()
	{
		return m_size == 0;
	}
	void print()
	{
		cout << "Array: ";
		cout << "capacity = " << m_capacity << ", " << "size = " << m_size << endl;
		cout << "[";
		for (int i = 0; i < m_size; i++)
		{
			cout << m_data[i];
			if (i != m_size - 1)
			{
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
	//增加操作
	void add(int index, T num);
	void addFirst(T num);
	void addLast(T num);
	//删除操作
	T remove(int index);
	T removeFirst();
	T removeLast();
	void removeElement(T num);
	//修改操作
	void set(int index, T num);
	//查找操作
	T get(int index);
	int find(T num);
	bool contains(T num);
	//两个有序数组合并为一个有序数组
	T SortArray(Array<T> a, Array<T> b);
private:
	T *m_data;       //数组数据
	int m_capacity;  //数组容量
	int m_size;      //数组实际大小
};

template<class T>
void Array<T>::add(int index, T num)
{
	if (index < 0 || index > m_size)
	{
		cout << "添加位置非法!" << endl;
		return;
	}
	if (m_size >= m_capacity)
	{
		resize(2 * m_capacity);
	}
	for (int i = m_size; i > index; i--)
	{
		m_data[i] = m_data[i - 1];
	}
	m_data[index] = num;
	m_size++;
}

template<class T>
void Array<T>::addFirst(T num)
{
	add(0, num);
}

template<class T>
void Array<T>::addLast(T num)
{
	if (m_size >= m_capacity)
	{
		resize(2 * m_capacity);
	}
	m_data[m_size] = num;
	m_size++;
}

template<class T>
T Array<T>::remove(int index)
{
	if (index < 0 || inndex >= m_size)
	{
		cout << "删除位置非法!" << endl;
		return NULL;//也可以抛异常
	}
	T res = m_data[index];
	m_size--;
	for (int i = 0; i < m_size; i++)
	{
		m_data[i] = m_data[i + 1];
	}
	if (m_size < m_capacity / 4)
	{
		resize(m_capacity / 2);
	}
	return res;
}

template<class T>
T Array<T>::removeFirst()
{
	T res = m_data[0];
	remove(0);
	return res;
}

template<class T>
T Array<T>::removeLast()
{
	if (m_size == 0)
	{
		cout << "删除位置非法!" << endl;
		return NULL;
	}
	m_size--;
	if (m_size < m_capacity / 4)
	{
		resize(m_capacity / 2);
	}
	return m_data[m_size];
}

template<class T>
void Array<T>::removeElement(T num)
{
	int flag = find(num);
	if (flag != -1)
	{
		remove(flag);
	}
}

template<class T>
void Array<T>::set(int index, T num)
{
	if (index < 0 || index >= m_size)
	{
		cout << "修改位置非法!" << endl;
		return;
	}
	m_data[index] = num;
}

template<class T>
T Array<T>::get(int index)
{
	if (index < 0 || index >= m_size)
	{
		cout << "访问位置非法!" << endl;
		return NULL;
	}
	return m_data[index];
}

template<class T>
int Array<T>::find(T num)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_data[i] == num)
		{
			return i;
		}
	}
	return -1;
}

template<class T>
bool Array<T>::contains(T nun)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_data[i] == num)
		{
			return true;
		}
	}
	return false;
}

template<class T>
T Array<T>::SortArray(Array<T> a, Array<T> b)
{
	int c_size = a.m_size + b.m_size;
	T *c = new T[c_size];
	int ai = 0, bi = 0, ci = 0;             //三个标志位
	while (ai < a.m_size && bi < b.m_size)  //两个数组否没有到达末尾时
	{
		if (a.m_data[ai] < b.m_data[bi])
			c[ci++] = a.m_data[ai++];
		else
			c[ci++] = b.m_data[bi++];
	}
	if (ai == a.m_size)                     //到达末尾时，直接把b数组剩余元素拷贝到c数组
	{
		while (bi < b.m_size)
		{
			c[ci++] = b.m_data[bi++];
		}
	}
	if (bi == b.m_size)
	{
		while (ai < a.m_size)
			c[ci++] = a.m_data[ai++];
	}

	for (int i = 0; i < c_size; i++)
	{
		cout << c[i];
		if (i != c_size - 1)
		{
			cout << ", ";
		}
	}
}

