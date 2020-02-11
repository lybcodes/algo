//单链表实现
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct Node
{
	int data;
	struct Node *next;
}*LinkedList, LNode;

//尾插法创建单链表
void CreateLinkedList(LinkedList &L, int n)    
{
	L = (LinkedList)malloc(sizeof(LNode));     //初始化
	L->next = NULL;
	L->data = 0;
	LinkedList Tail = L;                       //头尾指针L和Tial指向一块内存，现在就一个节点
	cout << "Enter" << n << "number" << endl;
	for (int i = 0; i < n; i++)
	{
		LinkedList Temp = (LinkedList)malloc(sizeof(LNode));
		cin >> Temp->data;
		Tail->next = Temp;  //尾节点的指针域指向新创建的节点(这里头就是尾都公用一块内存)
		Tail = Temp;        //此时Tail的地址不再是头结点L，而是新创建的节点Temp
		Temp = NULL;        //将Temp指针赋为空，此时L就是头结点，Tail就是尾节点。循环创建                     节点插入尾部
		L->data++; //计数 也就是头结点里存的数据是链表的节点数
	}
	Tail->next = NULL; //尾节点指向空
}
//获取节点(要知道第i个节点 从头结点往后遍历)
bool GetElem(int &e, int i, LinkedList L)
{
	while (L != NULL && i > 0)
	{
		i--;
		L = L->next;
	}
	if (i == 0 && L != NULL)
	{
		e = L->data;
		return true;
	}
	else return false;
}

//插入节点
bool InsertElem(int e, int i, LinkedList L)
{
	if (i > L->data + 1 || i < 1)	return false;
	else
	{
		L->data++;
		while (i > 1)
		{
			i--;
			L = L->next;
		}
		LinkedList Temp = (LinkedList)malloc(sizeof(LNode));
		Temp->data = e;
		Temp->next = L->next;
		L->next = Temp;
		Temp = NULL;
		return true;
	}
}

//删除节点
bool DeleteElem(int i, LinkedList L)
{
	if (i > L->data || i < 1)	return false;
	else
	{
		L->data--;
		while (i > 1)
		{
			i--;
			L = L->next;
		}
		LinkedList Temp = (LinkedList)malloc(sizeof(LNode));
		Temp = L->next;  //Temp现在指向待删除的节点.所以Temp的next指向待删除节点的下一个节点
		L->next = Temp->next; 
		free(Temp);
		Temp = NULL;
		return true;
	}
}

//销毁单链表（整个内存都没有了）
bool DestoryLinkedList(LinkedList &L)
{
	if (L->next != NULL) //从尾节点开始删除
	{
		DestoryLinkedList(L->next); //这是一个递归的过程，先一层一层递到尾，删除尾节点之后，                             再往回归，从尾部一个一个节点都删除
	}
	free(L);
	L = NULL;
	return true;
}

//清空单链表（只剩一个头结点了） 
bool ClearLinkedList(LinkedList &L)
{
	DestoryLinkedList(L->next);
	L->next = NULL;
	L->data = 0;
	return true;
}

//遍历
void GetLinkedList(LinkedList L)
{
	LinkedList Head = L->next; 
	while (Head != NULL)
	{
		cout << Head->data << endl;
		Head = Head->next;
	}
}


//单链表反转（递归法）
LinkedList reverseList(LinkedList L)
{
	if (L == NULL || L->next == NULL)
	{
		return L;
	}
	else
	{
		//先反转后面的链表
		LinkedList newList = reverseList(L->next);
		//再将当前节点设置为后面节点的后续节点
		L->next->next = L;
		L->next = NULL;

		return newList;
	}
}
//单链表反转（迭代法）
LinkedList reverseList2(LinkedList L)
{
	LinkedList pre = NULL;
	LinkedList pnext = NULL;
	LinkedList tail = NULL;
	//遍历
	while (L != NULL)
	{
		pnext = L->next;
		if (pnext == NULL)
			tail = L;
		L->next = pre;
		pre = L;
		L = pnext;
	}
	return tail;
}

//查找链表的中间节点
//定义两个指针，p每次移动两下，q每次移动一下，当p指向最后一个节点时，q就是中间的节点
LinkedList FindMidNode(LinkedList L)
{
	if (L == NULL)
		return NULL;
	if (L->next == NULL || L->next->next == NULL)
		return L;
	LinkedList p = L;
	LinkedList q = L;

	while (p->next != NULL && p->next->next != NULL)
	{
		p = p->next->next;
		q = q->next;
	}
	return q;
}

//合并两个有序链表(迭代法)
LinkedList mergeTwoList(LinkedList L1, LinkedList L2)
{
	LinkedList p = L1->next;
	LinkedList q = L2->next;
	LinkedList newhead = (LinkedList)malloc(sizeof(LNode));
	LinkedList tail = newhead;
	while (p && q)
	{
		if (p->data < q->data)
		{
			tail->next = p;
			p = p->next;
		}
		else
		{
			tail->next = q;
			q = q->next;
		}
		tail = tail->next;
	}
	//下面是有一个链表走到了尾部
	if (p)
		tail->next = p;
	if (q)
		tail->next = q;

	LinkedList r = newhead;
	newhead = newhead->next;
	delete r;
	r = NULL;
	return newhead; //不带头结点的
}
//合并两个有序链表(递归法)
LinkedList mergeTwoList2(LinkedList L1, LinkedList L2)
{
	//有一个链表为空直接返回另一个
	if (!L1)
		return L2;
	if (!L2)
		return L1;
	//递归
	if (L1->next->data < L2->next->data)
	{
		L1->next->next = mergeTwoList2(L1->next->next, L2->next);
		return L1;
	}
	else
	{
		L2->next->next = mergeTwoList2(L1->next, L2->next->next);
		return L2;
	}
}



#if 0
int main()
{
	int n, i, Elem;
	bool Flag;
	LinkedList L;
	cout << "How many Elems do you want to create?" << endl;
	cin >> n;
	CreateLinkedList(L, n);
	cout << "Here is what they look like:" << endl;
	GetLinkedList(L);
	FindMidNode(L);
	//LinkedList newList = reverseList2(L);
	//GetLinkedList(newList);
	cout << "which position of Elem do you want?" << endl;
	cin >> i;
	Flag = GetElem(Elem, i, L);
	if (Flag == true)
		cout << Elem << endl;
	else
		cout << "No matching Elem" << endl;
	cout << "what Elem you wanna insert,and where?" << endl;
	cout << "Elem :";
	cin >> Elem;
	cout << "Position :";
	cin >> i;
	Flag = InsertElem(Elem, i, L);
	if (Flag == true)
	{
		cout << "succeeded" << endl;
		GetLinkedList(L);
	}
	else
		cout << "Failed" << endl;
	cout << "which position of Elem do you want to delete:" << endl;
	cin >> i;
	Flag = DeleteElem(i, L);
	if (Flag == true)
	{
		cout << "succeeded" << endl;
		GetLinkedList(L);
	}
	else
		cout << "Failed" << endl;
	if (ClearLinkedList(L))		cout << "linkedList Cleared" << endl;
	GetLinkedList(L);
	if (DestoryLinkedList(L))	cout << "LinkedList Destoryed" << endl;
	if (L == NULL)	cout << "check" << endl;

	return 0;

}
#endif