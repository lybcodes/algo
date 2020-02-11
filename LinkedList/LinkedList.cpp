//������ʵ��
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct Node
{
	int data;
	struct Node *next;
}*LinkedList, LNode;

//β�巨����������
void CreateLinkedList(LinkedList &L, int n)    
{
	L = (LinkedList)malloc(sizeof(LNode));     //��ʼ��
	L->next = NULL;
	L->data = 0;
	LinkedList Tail = L;                       //ͷβָ��L��Tialָ��һ���ڴ棬���ھ�һ���ڵ�
	cout << "Enter" << n << "number" << endl;
	for (int i = 0; i < n; i++)
	{
		LinkedList Temp = (LinkedList)malloc(sizeof(LNode));
		cin >> Temp->data;
		Tail->next = Temp;  //β�ڵ��ָ����ָ���´����Ľڵ�(����ͷ����β������һ���ڴ�)
		Tail = Temp;        //��ʱTail�ĵ�ַ������ͷ���L�������´����Ľڵ�Temp
		Temp = NULL;        //��Tempָ�븳Ϊ�գ���ʱL����ͷ��㣬Tail����β�ڵ㡣ѭ������                     �ڵ����β��
		L->data++; //���� Ҳ����ͷ�����������������Ľڵ���
	}
	Tail->next = NULL; //β�ڵ�ָ���
}
//��ȡ�ڵ�(Ҫ֪����i���ڵ� ��ͷ����������)
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

//����ڵ�
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

//ɾ���ڵ�
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
		Temp = L->next;  //Temp����ָ���ɾ���Ľڵ�.����Temp��nextָ���ɾ���ڵ����һ���ڵ�
		L->next = Temp->next; 
		free(Temp);
		Temp = NULL;
		return true;
	}
}

//���ٵ����������ڴ涼û���ˣ�
bool DestoryLinkedList(LinkedList &L)
{
	if (L->next != NULL) //��β�ڵ㿪ʼɾ��
	{
		DestoryLinkedList(L->next); //����һ���ݹ�Ĺ��̣���һ��һ��ݵ�β��ɾ��β�ڵ�֮��                             �����ع飬��β��һ��һ���ڵ㶼ɾ��
	}
	free(L);
	L = NULL;
	return true;
}

//��յ�����ֻʣһ��ͷ����ˣ� 
bool ClearLinkedList(LinkedList &L)
{
	DestoryLinkedList(L->next);
	L->next = NULL;
	L->data = 0;
	return true;
}

//����
void GetLinkedList(LinkedList L)
{
	LinkedList Head = L->next; 
	while (Head != NULL)
	{
		cout << Head->data << endl;
		Head = Head->next;
	}
}


//������ת���ݹ鷨��
LinkedList reverseList(LinkedList L)
{
	if (L == NULL || L->next == NULL)
	{
		return L;
	}
	else
	{
		//�ȷ�ת���������
		LinkedList newList = reverseList(L->next);
		//�ٽ���ǰ�ڵ�����Ϊ����ڵ�ĺ����ڵ�
		L->next->next = L;
		L->next = NULL;

		return newList;
	}
}
//������ת����������
LinkedList reverseList2(LinkedList L)
{
	LinkedList pre = NULL;
	LinkedList pnext = NULL;
	LinkedList tail = NULL;
	//����
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

//����������м�ڵ�
//��������ָ�룬pÿ���ƶ����£�qÿ���ƶ�һ�£���pָ�����һ���ڵ�ʱ��q�����м�Ľڵ�
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

//�ϲ�������������(������)
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
	//��������һ�������ߵ���β��
	if (p)
		tail->next = p;
	if (q)
		tail->next = q;

	LinkedList r = newhead;
	newhead = newhead->next;
	delete r;
	r = NULL;
	return newhead; //����ͷ����
}
//�ϲ�������������(�ݹ鷨)
LinkedList mergeTwoList2(LinkedList L1, LinkedList L2)
{
	//��һ������Ϊ��ֱ�ӷ�����һ��
	if (!L1)
		return L2;
	if (!L2)
		return L1;
	//�ݹ�
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