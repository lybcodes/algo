#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#if 0

//两个有序数组合并
void merge(int a[], int middle, int left, int right)
{
	int *tmp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;

	tmp = (int *)malloc((right - left + 1)*sizeof(int));
	assert(tmp != NULL);

	i = left;
	j = middle + 1;

	while (1)
	{
		if ((i > middle) || (j > right)) break;
		if (a[i] > a[j]) tmp[k++] = a[j++];
		else tmp[k++] = a[i++];
	}

	if (i > middle)
	{
		while (j <= right)
		{
			tmp[k++] = a[j++];
		}
	}
	else
	{
		while (i <= middle)
		{
			tmp[k++] = a[i++];
		}
	}

	//memcpy函数的功能是从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
	memcpy((a + left), tmp, (right - left + 1)*sizeof(int));

	free(tmp);
	return;
}

//归并算法
void merge_sort(int a[], int left, int right)
{
	int middle = 0;

	//递归终止条件
	if (left >= right)
	{
		return;
	}

	middle = (left + right) / 2;

	merge_sort(a, left, middle);
	merge_sort(a, middle + 1, right);

	merge(a, middle, left, right);

	return;
}

void dump(int a[], int size)
{
	int i = 0;

	if (size == 0)
	{
		return;
	}

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
	int a[10] = { 30,20,10,15,4,8,40,80,20,9 };

	merge_sort(a, 0, 9);

	dump(a, 10);

	system("pause");
	return 0;
}

#endif