/*我们有一个数字序列包含 n 个不同的数字，如何求出这个序列中的最长递增子序列长度？
  比如 2, 9, 3, 6, 5, 1, 7 这样一组数字序列，它的最长递增子序列就是 2, 3, 5, 7，所以最长递增子序列的长度是 4
 */

/*
动态规划求 a 的最上升长子序列长度
递推公式:  a[0...i] 的最长子序列为: a[i] 之前所有比它小的元素中子序列长度最大的 + 1
这种方法的时间复杂度为O(n^2) 并不是最优的
*/

#include <iostream>
using namespace std;

int longestSubsequence(int *a, int n)
{
	//创建一个数组，索引i对应考察元素的下标，储存arr[]的最长上升子序列
	int *lss_length = new int[n];
	//第一个元素哨兵处理
	lss_length[0] = 1;
	//动态规划求解最长子序列
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