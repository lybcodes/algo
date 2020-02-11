/*������һ���������а��� n ����ͬ�����֣���������������е�����������г��ȣ�
  ���� 2, 9, 3, 6, 5, 1, 7 ����һ���������У���������������о��� 2, 3, 5, 7����������������еĳ����� 4
 */

/*
��̬�滮�� a ���������������г���
���ƹ�ʽ:  a[0...i] ���������Ϊ: a[i] ֮ǰ���б���С��Ԫ���������г������� + 1
���ַ�����ʱ�临�Ӷ�ΪO(n^2) ���������ŵ�
*/

#include <iostream>
using namespace std;

int longestSubsequence(int *a, int n)
{
	//����һ�����飬����i��Ӧ����Ԫ�ص��±꣬����arr[]�������������
	int *lss_length = new int[n];
	//��һ��Ԫ���ڱ�����
	lss_length[0] = 1;
	//��̬�滮����������
	int i, j, max;
	for (i = 1; i < n; i++)
	{
		max = 1;
		for (j = 0; j < i; j++)
		{
			if (a[i] > a[j] && lss_length[j] >= max)
			{
				max = lss_length[j] + 1;
			}
		}
		lss_length[i] = max;
	}
	int value = lss_length[n - 1];
	delete[]lss_length;
	return value;
}

void main()
{
	const int n = 7;
	int arr[n] = { 2,9,3,6,5,1,7 };
	cout << longestSubsequence(arr, n) << endl;
	system("pause");
}