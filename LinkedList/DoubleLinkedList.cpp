#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct LNode
{
	int date;
	struct LNode *pre;
	struct LNode *next;
}*DoubleLinkedList, LNode;

void CreatDoubleLinkedList(DoubleLinkedList &L, int n)
{
	L = (DoubleLinkedList)malloc(sizeof(LNode));
	L->pre = NULL;
	L->next = NULL;
	L->date = 0;
	DoubleLinkedList Tail = L;
	cout << "Enter " << n << " numbers" << endl;
	for (int i = 0; i < n; i++)
	{
		DoubleLinkedList Temp = (DoubleLinkedList)malloc(sizeof(LNode));
		cin >> Temp->date;
		Tail->next = Temp;
		Temp->pre = Tail;
		Tail = Temp;
		L->date++;
	}
	Tail->next = NULL;
}

bool GetElem(int &e, int i, DoubleLinkedList L)
{
	while (L != NULL && i > 0)
	{
		i--;
		L = L->next;
	}
	if (i == 0 && L != NULL)
	{
		e = L->date;
		return true;
	}
	else return false;
}

bool InsertElem(int e, int i, DoubleLinkedList L)
{
	if (i > L->date + 1 || i < 1)
		return false;
	else
	{
		L->date++;
		while (i > 1)
		{
			L = L->next;
			i--;
		}
		DoubleLinkedList Temp = (DoubleLinkedList)malloc(sizeof(LNode));
		Temp->date = e;
		if (L->next != NULL)
		{
			Temp->next = L->next;
			Temp->pre = L;
			L->next->pre = Temp;
			L->next = Temp;
		}
		else
		{
			Temp->pre = L;
			L->next = Temp;
			Temp->next = NULL;
		}
	}
}

bool DeleteElem(int i, DoubleLinkedList L)
{
	if (i > L->date || i < 1)
		return false;
	else
	{
		L->date--;
		while (i > 1)
		{
			L = L->next;
			i--;
		}
		DoubleLinkedList Temp = (DoubleLinkedList)malloc(sizeof(LNode));
		Temp = L->next;
		if (L->next->next != NULL)
		{
			L->next->next->pre = L;
			L->next = L->next->next;
		}
		else
			L->next = NULL;
		free(Temp);
		Temp = NULL;
		return true;
	}
}

bool DestoryDoubleLinkedList(DoubleLinkedList L)
{
	if (L->next != NULL)
		DestoryDoubleLinkedList(L->next);
	free(L);
	L = NULL;
	return true;
}

bool ClearDoubleLinkedList(DoubleLinkedList L)
{
	DestoryDoubleLinkedList(L->next);
	L->next = NULL;
	L->date = 0;
	return true;
}

void GetDoubleLinkedList(DoubleLinkedList L)
{
	DoubleLinkedList Head = L->next;
	while (Head != NULL)
	{
		cout << Head->date << endl;
		Head = Head->next;
	}
}

