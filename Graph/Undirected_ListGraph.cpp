#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_VERTEX_NUM 20 
#define VertexType int  


//边表结点 
typedef struct ArcNode
{
	int Adjvex; //注意:这个索引值是边表节点自己在数组中的索引值
	ArcNode *nextarc;
	int weigth; //如果是有权图加这句
}ArcNode;


//顶点表结点 
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
	cout << "请输入节点数和边数：";
	cin >> g->vexnum >> g->arcnum;

	cout << "请输入每个顶点保存的数据：" << endl;
	for (int i = 0; i < g->vexnum; i++)
	{
		cout << "vertex" << i << ":";
		cin >> g->vertices[i].data;
		g->vertices[i].firstarc = NULL;
	}

	cout << "请输入每条边的两个顶点在数组中的下标，中间用空格分隔" << endl;
	for (int j = 0; j < g->arcnum; j++)
	{
		cout << "请输入第" << j << "条边：" << endl;
		cin >> start >> end;
		ArcNode *node = (ArcNode*)malloc(sizeof(ArcNode));
		node->Adjvex = end;
		node->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = node; //start和end这两个点之间有一条边 start指向end
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
	cout << "邻接表为：" << endl;
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