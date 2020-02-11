/********************
>字符串匹配算法
>暴力匹配算法（朴素匹配算法）模式串逐位后移
********************/

#include <iostream>
#include <string>

using namespace std;

//从pos位置开始返回子串在主串中的位置
int BF(string M, string T, int pos)
{
	int i = pos; //子串位置
	int j = 0;   //模式串下标
	int M_len = M.length(); //主串长度
	int T_len = T.length(); //模式串长度

	if (pos < 0 && pos > M_len)
		return -1;

	while (i < M_len && j < T_len)
	{
		if (M[i] == T[j])
		{
			++i;
			++j;
		}
		else
		{
			//主串长度n,模式串长度m，就有n-m+1个子串与模式串比较
			i = i - j + 1; //这里就是主串往后移一位
			j = 0;
		}
	}
	if (j >= T_len)
		return i - T_len;
	else
		return -1;
}

int main()
{
	string M = "abcdefabcdx";
	string T = "abcdx";
	cout << BF(M, T, 5) << endl;
	
	system("pause");
	return 0;
}