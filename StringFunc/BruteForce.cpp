/********************
>�ַ���ƥ���㷨
>����ƥ���㷨������ƥ���㷨��ģʽ����λ����
********************/

#include <iostream>
#include <string>

using namespace std;

//��posλ�ÿ�ʼ�����Ӵ��������е�λ��
int BF(string M, string T, int pos)
{
	int i = pos; //�Ӵ�λ��
	int j = 0;   //ģʽ���±�
	int M_len = M.length(); //��������
	int T_len = T.length(); //ģʽ������

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
			//��������n,ģʽ������m������n-m+1���Ӵ���ģʽ���Ƚ�
			i = i - j + 1; //�����������������һλ
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