#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;


/*�ڽӱ���*/
const int MAX_NUM = 20;
const int INF = 9999;

struct Node
{
	int id;
	int w;
	//���ȼ����еײ�Ĭ���Ǵ󶥶ѣ���������<
	friend bool operator <(Node n1, Node n2)
	{
		return (n1.w > n2.w); //��С��������
	}
};

//���¾���
vector<Node>dist(MAX_NUM);

//�߱���
struct EdgeNode
{
	int adjoinVertex; //�߱�ڵ��Լ��ڶ���������е�����ֵ
	int weight;
	EdgeNode *next;

	EdgeNode(int a = 0, int w = 0, EdgeNode *n = NULL) :adjoinVertex(a), weight(w), next(n) {};
};

//�������
struct Adjoinlist
{
	int data;
	EdgeNode *firstEdge;
};

struct Graph
{
	int numVertex; //������
	int numEdge;   //����
	vector<Adjoinlist>adjoinlist;

	Graph(int n = 10) :adjoinlist(n) {};
};

void createGraph(Graph &g, int numEdge, int numVertex)
{
	g.numEdge = numEdge;
	g.numVertex = numVertex;

	for (int i = 0; i < g.numVertex; i++)
	{
		g.adjoinlist[i].firstEdge = NULL;
	}

	int v_i, v_j, w; //v_i -> v_j with weight w 
	EdgeNode *node;
	for (int i = 0; i < g.numVertex; i++)
	{
		cout << "�������ռ������������ݺ�Ȩֵ��";
		cin >> v_i >> v_j >> w;
		node = new EdgeNode(v_j, w, g.adjoinlist[v_i].firstEdge);
		g.adjoinlist[v_i].firstEdge = node;
	}
}

//Dijkstra�㷨
void Dijkstra(Graph g, int start)
{
	vector<bool> visited(g.numVertex); //�����Ѿ����ʹ��Ķ���
	priority_queue<Node>dijQueue;      //���ȼ�����

	//��ʼ�������
	for (int i = 0; i < g.numVertex; i++)
	{
		dist[i].id = i;
		dist[i].w = INF;
		visited[i] = false;
	}
	dist[start].w = 0;               //��ʼ��ȨֵΪ0
	dijQueue.push(dist[start]);      
	EdgeNode *node;
	while (!dijQueue.empty())
	{
		Node temp = dijQueue.top();
		dijQueue.pop();
		int u = temp.id;
		if (visited[u])
			continue;
		visited[u] = true;
		node = g.adjoinlist[u].firstEdge;
		while (node)
		{
			if ((!visited[node->adjoinVertex]) && (dist[node->adjoinVertex].w > dist[u].w + node->weight))
			{
				dist[node->adjoinVertex].w = dist[u].w + node->weight;
				dijQueue.push(dist[node->adjoinVertex]);
			}
			node = node->next;
		}
	}
} 

int main()
{
	int	numEdge, numVertex;
	cout << "���붥�����ͱ�����";
	cin >> numEdge >> numVertex;
	Graph g;
	createGraph(g, numEdge, numVertex);
	cout << "��������ͼ����" << endl;
	for (int i = 1; i <= numEdge; i++)  
	{
		EdgeNode *node = g.adjoinlist[i].firstEdge;
		cout << i;
		while (node)
		{
			cout << " -> " << node->adjoinVertex;
			node = node->next;
		}
		cout << endl;
	}
	int start, end;
	cout << "������ʼ����ֹ���㣺";
	cin >> start >> end;
	Dijkstra(g, start);
	if (dist[end].w != INF)
	{
		cout << "��̾�����" << start << "��" << end << "֮�� " << "��" << dist[end].w << endl;
	}
	else
		cout << "����·�������ڣ�" << endl;

	system("pause");
	return 0;
}


