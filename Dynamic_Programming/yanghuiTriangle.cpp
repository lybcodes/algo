/*���ö�̬�滮��������������*/

#include <iostream>

using namespace std;

//�ö�ά������ģ��������ǣ���һ��һ���㣬�ڶ���������......
int matrix[5][5] = { {5},{7,8},{2,3,4},{4,9,6,1},{2,7,9,4,5} };
#if 0
void main()
{
	int status[5][8];
	status[0][0] = 5; //status[0][0] = matrix[0][0] 
	for (int i = 1; i < 5; i++)  //��̬�滮 ״̬ת��
	{
		for (int j = 0; j <= i; j++)
		{
			if (j == 0)
				status[i][j] = status[i - 1][j] + matrix[i][j]; //ת�Ʒ���
			else if (j > 0 && j < i)
			{
				int v = status[i - 1][j] + matrix[i][j];
				int w = status[i - 1][j - 1] + matrix[i][j];
				if (v < w)
					status[i][j] = v;
				else
					status[i][j] = w;
			}
			else if (j == i)
				status[i][j] = status[i - 1][j - 1] + matrix[i][j];
		}
	}
	int min = status[4][0];
	for (int w = 1; w < 5; w++)
	{
		if (status[4][w] < min)
			min = status[4][w];
	}
	cout << min << endl;
	system("pause");
}
#endif