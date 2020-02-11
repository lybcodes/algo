#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_VERTEX_NUM 20 
#define VertexType int  


//�߱��� 
typedef struct ArcNode
{
	int Adjvex; //ע��:�������ֵ�Ǳ߱�ڵ��Լ��������е�����ֵ
	ArcNode *nextarc;
	int weigth; //�������Ȩͼ�����
}ArcNode;


//������� 
typedef struct VNode 
{
	VertexType data;
	ArcNode *firstarc;
}AdjList[MAX_VERTEX_NUM];


typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;


void CreateAL(ALGraph *g)
{
	int end, start;
	cout << "������ڵ����ͱ�����";
	cin >> g->vexnum >> g->arcnum;

	cout << "������ÿ�����㱣������ݣ�" << endl;
	for (int i = 0; i < g->vexnum; i++)
	{
		cout << "vertex" << i << ":";
		cin >> g->vertices[i].data;
		g->vertices[i].firstarc = NULL;
	}

	cout << "������ÿ���ߵ����������������е��±꣬�м��ÿո�ָ�" << endl;
	for (int j = 0; j < g->arcnum; j++)
	{
		cout << "�������" << j << "���ߣ�" << endl;
		cin >> start >> end;
		ArcNode *node = (ArcNode*)malloc(sizeof(ArcNode));
		node->Adjvex = end;
		node->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = node; //start��end��������֮����һ���� startָ��end
	}
}


void PrintLink(ALGraph *g, ArcNode *next)
{
	while (next != NULL)
	{
		cout << g->vertices[next->Adjvex].data << " ";
		next = next->nextarc;
	}
	cout << endl;
}


void disp(ALGraph *g)
{
	cout << "�ڽӱ�Ϊ��" << endl;
	for (int i = 0; i < g->vexnum; i++)
	{
		cout << g->vertices[i].data << " ";
		PrintLink(g, g->vertices[i].firstarc);
	}
}

#if 0
int main()
{
	ALGraph *g = (ALGraph*)malloc(sizeof(ALGraph));
	CreateAL(g);
	disp(g);

	system("pause");
	return 0;
}
#endif