#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct LNode
{
	int date;
	struct LNode *next;
}*CircleLinkedList, LNode;

//尾插法创建循环链表
void CreatLinkedList(CircleLinkedList &L, int n)
{
	L = (CircleLinkedList)malloc(sizeof(LNode));
	L->next = NULL;
	L->date = 0;
	CircleLinkedList Tail = L;//头尾指针指向同一块内存
	cout << "Enter " << n << "numbers" << endl;
	for (int i = 0; i < n; i++)
	{
		CircleLinkedList Temp = (CircleLinkedList)malloc(sizeof(LNode));
		cin >> Temp->date;
		Tail->next = Temp;
		Tail = Temp;
		L->date++;
	}
	Tail->next = L;
}

//获取节点
bool GetElem(int &e, int i, CircleLinkedList L)
{
	CircleLinkedList Head = L;
	while (L->next != Head && i > 0)
	{
		i--;
		L = L->next;
	}
	if (i == 0 && L != Head)
	{
		e = L->date;
		return true;
	}
	else return false;
}

//插入节点
bool InsertElem(int e, int i, CircleLinkedList L)
{
	if (i > L->date + 1 || i < 1)	return false;
	else
	{
		L->date++;
		while (i > 1)
		{
			i--;
			L = L->next;
		}
		CircleLinkedList Temp = (CircleLinkedList)malloc(sizeof(LNode));
		Temp->date = e;
		Temp->next = L->next;
		L->next = Temp;
		return true;
	}
}

//删除节点
bool DeleteElem(int i, CircleLinkedList L)
{
	if (i > L->date || i < 1)	return false;
	else
	{
		L->date--;
		while (i > 1)
		{
			i--;
			L = L->next;
		}
		CircleLinkedList Temp = (CircleLinkedList)malloc(sizeof(LNode));
		Temp = L->next;
		L->next = Temp->next;
		free(Temp);
		Temp = NULL;
		return true;
	}
}

//销毁
bool DestoryCircleLinkedList(CircleLinkedList L, CircleLinkedList Head)
{
	if (L->next != Head)
		DestoryCircleLinkedList(L->next, Head);
	free(L);
	L = NULL;
	return true;
}

//清空
bool ClearCircleLinkedList(CircleLinkedList L, CircleLinkedList Head)
{
	DestoryCircleLinkedList(L->next, Head);
	L->next = Head;
	L->date = 0;
	return true;
}

//遍历
void GetCircleLinkedList(CircleLinkedList L)
{
	CircleLinkedList Head = L;
	L = L->next;
	while (L != Head)
	{
		cout << L->date << endl;
		L = L->next;
	}
}

#if 0
int main()
{
	int n, i, Elem;
	bool Flag;
	CircleLinkedList L;
	cout << "How many Elems do you want to create?" << endl;
	cin >> n;
	CreatLinkedList(L, n);
	cout << "Here is what they look like:" << endl;
	GetCircleLinkedList(L);
	cout << "Which position of Elem do you want?" << endl;
	cin >> i;
	Flag = GetElem(Elem, i, L);
	if (Flag == true)
	{
		cout << Elem << endl;
	}
	else
		cout << "No matching Elem" << endl;
	cout << "What Elem you wanna insert, and where?" << endl;
	cout << "Elem :";
	cin >> Elem;
	cout << "Position :";
	cin >> i;
	Flag = InsertElem(Elem, i, L);
	if (Flag == true)
	{
		cout << "succeeded" << endl;
		GetCircleLinkedList(L);
	}
	else
		cout << "Failed" << endl;
	cout << "Which position of Elem do you want to delete :" << endl;
	cin >> i;
	Flag = DeleteElem(i, L);
	if (Flag == true)
	{
		cout << "succeeded" << endl;
		GetCircleLinkedList(L);
	}
	else
		cout << "Failed" << endl;
	if (ClearCircleLinkedList(L, L))	 cout << "CircleLinkedList Cleared" << endl;
	GetCircleLinkedList(L);
	if (DestoryCircleLinkedList(L, L))	cout << "CircleLinkedList Destoryed" << endl;
	if (L == NULL)	cout << "checked" << endl;

	return 0;
}
#endif