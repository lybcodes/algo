#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_VERTEX 4
#if 0
typedef char Datetype;

typedef struct
{
	Datetype vertexArr[MAX_VERTEX]; //顶点元素数组
	int arcArr[MAX_VERTEX][MAX_VERTEX]; //表示边的矩阵
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
		printf("输入第%d个顶点值\n", i + 1);
		getchar();
		scanf(" %c", &(pGraph->vertexArr[i]));
	}

	for (int j = 0; j < MAX_VERTEX; j++)
	{
		for (int i = j + 1; i < MAX_VERTEX; i++)
		{
			printf("若元素%c有指向%c的弧，则输入1，否则输入0\n", pGraph->vertexArr[i], pGraph->vertexArr[j]);
			getchar();
			scanf("%d", &(pGraph->arcArr[j][i]));

			printf("若元素%c有指向%c的弧，则输入1，否则输入0\n", pGraph->vertexArr[j], pGraph->vertexArr[i]);
			getchar();
			scanf("%d", &(pGraph->arcArr[i][j]));
		}
	}
}

void ArrayGraph_show(ArrayGraph *pGraph)
{
	printf("\n定点元素如下\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("%-5c", pGraph->vertexArr[i]);
	}
	printf("\n\n");
	puts("弧矩阵如下\n\n");
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