#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;


/*邻接表储存*/
const int MAX_NUM = 20;
const int INF = 9999;

struct Node
{
	int id;
	int w;
	//优先级队列底层默认是大顶堆，这里重载<
	friend bool operator <(Node n1, Node n2)
	{
		return (n1.w > n2.w); //从小到大排列
	}
};

//更新距离
vector<Node>dist(MAX_NUM);

//边表结点
struct EdgeNode
{
	int adjoinVertex; //边表节点自己在顶点表数组中的索引值
	int weight;
	EdgeNode *next;

	EdgeNode(int a = 0, int w = 0, EdgeNode *n = NULL) :adjoinVertex(a), weight(w), next(n) {};
};

//顶点表结点
struct Adjoinlist
{
	int data;
	EdgeNode *firstEdge;
};

struct Graph
{
	int numVertex; //顶点数
	int numEdge;   //边数
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
		cout << "输入边所占两个顶点的数据和权值：";
		cin >> v_i >> v_j >> w;
		node = new EdgeNode(v_j, w, g.adjoinlist[v_i].firstEdge);
		g.adjoinlist[v_i].firstEdge = node;
	}
}

//Dijkstra算法
void Dijkstra(Graph g, int start)
{
	vector<bool> visited(g.numVertex); //储存已经访问过的顶点
	priority_queue<Node>dijQueue;      //优先级队列

	//初始化距离表
	for (int i = 0; i < g.numVertex; i++)
	{
		dist[i].id = i;
		dist[i].w = INF;
		visited[i] = false;
	}
	dist[start].w = 0;               //起始点权值为0
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
	cout << "输入顶点数和边数：";
	cin >> numEdge >> numVertex;
	Graph g;
	createGraph(g, numEdge, numVertex);
	cout << "所构建的图如下" << endl;
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
	cout << "输入起始和终止顶点：";
	cin >> start >> end;
	Dijkstra(g, start);
	if (dist[end].w != INF)
	{
		cout << "最短距离在" << start << "和" << end << "之间 " << "是" << dist[end].w << endl;
	}
	else
		cout << "这条路径不存在！" << endl;

	system("pause");
	return 0;
}


