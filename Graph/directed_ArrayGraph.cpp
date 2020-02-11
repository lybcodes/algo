#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_VERTEX 4
#if 0
typedef char Datetype;

typedef struct
{
	Datetype vertexArr[MAX_VERTEX]; //����Ԫ������
	int arcArr[MAX_VERTEX][MAX_VERTEX]; //��ʾ�ߵľ���
}ArrayGraph;

void ArrayGraph_init(ArrayGraph *pGraph)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		pGraph->vertexArr[i] = 0;
	}
}

void ArrayGraph_create(ArrayGraph *pGraph)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("�����%d������ֵ\n", i + 1);
		getchar();
		scanf(" %c", &(pGraph->vertexArr[i]));
	}

	for (int j = 0; j < MAX_VERTEX; j++)
	{
		for (int i = j + 1; i < MAX_VERTEX; i++)
		{
			printf("��Ԫ��%c��ָ��%c�Ļ���������1����������0\n", pGraph->vertexArr[i], pGraph->vertexArr[j]);
			getchar();
			scanf("%d", &(pGraph->arcArr[j][i]));

			printf("��Ԫ��%c��ָ��%c�Ļ���������1����������0\n", pGraph->vertexArr[j], pGraph->vertexArr[i]);
			getchar();
			scanf("%d", &(pGraph->arcArr[i][j]));
		}
	}
}

void ArrayGraph_show(ArrayGraph *pGraph)
{
	printf("\n����Ԫ������\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("%-5c", pGraph->vertexArr[i]);
	}
	printf("\n\n");
	puts("����������\n\n");
	printf("%-2c", ' ');
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("%-5c", pGraph->vertexArr[i]);
	}
	putchar('\n');

	for (int j = 0; j < MAX_VERTEX; j++)
	{
		printf("%-2c", pGraph->vertexArr[j]);
		for (int i = 0; i < MAX_VERTEX; i++)
		{
			printf("%-5d", pGraph->arcArr[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}


int main()
{
	ArrayGraph g;
	ArrayGraph_init(&g);
	ArrayGraph_create(&g);
	ArrayGraph_show(&g);

	system("pause");
	return 0;
}
#endif