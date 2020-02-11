#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#define MAX_VERTEX 4
#define INF 65535
//�������ı�����Ȩֵ�ģ����ֵ�������κ�һ���Ϸ���ֵ��ʲô����ֵ�ǺϷ����أ�����Ҫ����ͼ�ľ�����;���������ԣ����ǲ����ü򵥵�0,1������ߡ����2�������޹���������Ҳ������0��ʾ����Ϊ0Ҳ������һ���Ϸ���wieghtֵ���������һ�£���ε�����2���ط�֮�䲻�ɻ�ͨ����ô����֮��ĳ��̷��ǲ���������أ����ԣ�������Ҫ����ͼȨֵ���Ͷ���һ����Ӧ���͵����ֵ��������2������֮�䲻������

#if 0

typedef char DateType;   //�洢��Ԫ������
typedef int WeigthType;  //Ȩֵ������

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
		printf("�����%d������ֵ\n", i + 1);
		getchar();
		scanf(" %c", &(pGraph->vertexArr[i]));
	}
	for (int j = 0; j < MAX_VERTEX; j++)
	{
		for (int i = j + 1; i < MAX_VERTEX; i++)
		{
			printf("��Ԫ��%c��%c�бߣ�������Ȩֵ������������Чֵ%d\n", pGraph->vertexArr[j], pGraph->vertexArr[i], INF);
			getchar();
			scanf("%d", &(pGraph->edgeArr[j][i]));
			pGraph->edgeArr[i][j] = pGraph->edgeArr[j][i]; //�Գ�
		}
	}
}

void ArrayGraph_show(ArrayGraph *pGraph)
{
	printf("\n\n����Ԫ������\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		printf("%-5c", pGraph->vertexArr[i]);
	}
	printf("\n\n");

	puts("�߾�������");
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