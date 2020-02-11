#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/*���ֲ����㷨�ı�������
*1�����ҵ�һ�����ڸ�����ֵ��Ԫ��
*2���������һ�����ڸ�����ֵ��Ԫ��
*3�����ҵ�һ�����ڵ��ڸ�����ֵ��Ԫ��
*4�����ҵ�һ��С�ڵ��ڸ�����ֵ��Ԫ��
* */

/*1�����ҵ�һ�����ڸ�����ֵ��Ԫ��*/
int mybsearch_1(int a[], int size, int value)
{
	int mid = 0;
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		/*��ֹsize����̫���ǣ���left + right�����ݷ�ת����������, ʹ��λ������������2ʹ�����ܽ�һ���Ż�*/
		mid = left + ((right - left) >> 1);

		if (a[mid] < value)
			left = mid + 1;
		else if (a[mid] > value)
			right = mid - 1;
		else
		{
			if (mid == 0 || a[mid - 1] != value)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

/*2���������һ�����ڸ�����ֵ��Ԫ��*/
int mybsearch_2(int a[], int size, int value)
{
	int mid = 0;
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		mid = left + ((right - left) >> 1);

		if (a[mid] < value)
			left = mid + 1;
		else if (a[mid] > value)
			right = mid - 1;
		else
		{
			if (mid == (size - 1) || a[mid + 1] != value)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

/*3�����ҵ�һ�����ڵ��ڸ�����ֵ��Ԫ��*/
int mybsearch_3(int a[], int size, int value)
{
	int mid = 0;
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		mid = left + ((left - right) >> 1);

		if (a[mid] < value)
			left = mid + 1;
		else
		{
			if (mid == 0 || a[mid - 1] < value)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

/*4���������һ��С�ڵ��ڸ�����ֵ��Ԫ��*/
int mybsearch_4(int a[], int size, int value)
{
	int mid = 0;
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		mid = left + ((left - right) >> 1);

		if (a[mid] > value)
			right = mid - 1;
		else
		{
			if (mid == (size - 1) || a[mid + 1] > value)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

int main()
{
	int a[10] = { 5,6,6,9,10,11,11,22,33,33 };
	int data = 0;
	int i = 0;
	int res = 0;

	printf("\r\n");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\r\n");
	printf("\r\n����һ������");
	scanf("%d", &data);
	res = mybsearch_1(a, 10, data);
	printf("��һ������data[%d]���±���%d", data, res);

	printf("\r\n����һ������");
	scanf("%d", &data);
	res = mybsearch_2(a, 10, data);
	printf("���һ������data[%d]���±���%d", data, res);

	printf("\r\n����һ������");
	scanf("%d", &data);
	res = mybsearch_2(a, 10, data);
	printf("��һ�����ڵ���data[%d]���±���%d", data, res);

	printf("\r\n����һ������");
	scanf("%d", &data);
	res = mybsearch_2(a, 10, data);
	printf("���һ��С����data[%d]���±���%d", data, res);

	system("pause");
	return 0;
}