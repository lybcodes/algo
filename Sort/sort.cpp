#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ֺ��д��
#define SWAP(a,b) a^=b^=a^=b
/*
#define SWAP(a,b) \
do{\
	(a) ^= (b);\
	(b) ^= (a);\
	(a) ^= (b);\
}while(0)

#define SWAP(a,b)  {int temp; \
                     temp=*a;*a=*b;*b=temp;}
*/

#if 0
/*ð������*/
void bubble_sort(int a[], int size)
{
	int i = 0;
	int j = 0;
	int swap_flag = 0;
	if (size < 1)
		return;
	for (i = size - 1; i > 0; i--)//ð�ݴ���
	{
		swap_flag = 0;
		for (j = 0; j < i; j++)//ÿ��ð�ݱ�����Ԫ�ظ���
		{
			if (a[j] > a[j + 1])
			{
				SWAP(a[j], a[j + 1]);
				swap_flag = 1;
			}
		}
		//�����ݽ��� ˵���Ѿ����� ֱ���˳�
		if (swap_flag == 0)
			break;
	}
	return;
}

/*��������*/
void insert_sort(int a[], int size)
{
	int i = 0;
	int j = 0;
	int key = 0;
	for (i = 1; i < size; i++)
	{
		key = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

/*ѡ������*/
void select_sort(int a[], int size)
{
	int i = 0;
	int j = 0;
	int min = 0;
	for (i = 0; i < size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < size; j++)
		{
			if (a[j] < a[min])
				min = j;
		}
		if (min != i)
		{
			SWAP(a[i], a[min]);
		}
	}
	return;
}


void dump(int a[], int size)
{
	int i = 0;

	printf("\r\n");
	for (i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\r\n");
	return;
}

int main()
{
	int a[10] = { 9,11,4,15,16,3,20,44,5,10 };

	//bubble_sort(a,sizeof(a)/sizeof(int));
	//insert_sort(a,sizeof(a)/sizeof(int));
	select_sort(a, sizeof(a) / sizeof(int));

	dump(a, sizeof(a) / sizeof(int));

	return 0;
}

#endif