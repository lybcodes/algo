#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#define MAX_VERTEX 4
#define INF 65535
//无向网的边是有权值的，这个值可以是任何一个合法的值，什么样的值是合法的呢？这需要根据图的具体用途来定。所以，我们不能用简单的0,1来代表边。如果2个顶点无关联，他们也不能用0表示，因为0也可能是一个合法的wieght值。可有类比一下：如何地球上2个地方之间不可互通，那么他们之间的车程费是不是无穷大呢？所以，我们来要根据图权值类型定义一个相应类型的最大值，来代表2个顶点之间不关联。

#if 0

typedef char DateType;   //存储的元素类型
typedef int WeigthType;  //权值的类型

typedef struct
{
	DateType vertexArr[MAX_VERTEX];
	WeigthType edgeArr[MAX_VERTEX][MAX_VERTEX];
}ArrayGraph;

void ArrayGraph_init(ArrayGraph *pGraph)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		pGraph->edgeArr[i][i] = INF;
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
			printf("若元素%c和%c有边，则输入权值，否则输入无效值%d\n", pGraph->vertexArr[j], pGraph->vertexArr[i], INF);
			getchar();
			scanf("%d", &(pGraph->edgeArr[j][i]));
			pGraph->edgeArr[i][j] = pGraph->edgeArr[j][i]; //对称
		}
	}
}

void ArrayGraph_show(ArrayGraph *pGraph)
{
	printf("\n\n顶点元素如下\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("%-5c", pGraph->vertexArr[i]);
	}
	printf("\n\n");

	puts("边矩阵如下");
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
			if (pGraph->edgeArr[i][j] == INF)
				printf("%-5c", '#');
			else
				printf("%-5d", pGraph->edgeArr[i][j]);
		}
		putchar('\n');
	}
}

int main()
{
	ArrayGraph net;
	ArrayGraph_init(&net);
	ArrayGraph_create(&net);
	ArrayGraph_show(&net);

	system("pause");
	return 0;
}

#endif