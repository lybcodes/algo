#include <iostream>
#include <string>
#include <stack>
#include <queue>

//深度优先 (使用栈代替递归过程)
//广度优先（使用队列）

#define max_verts 10

using namespace std;

//邻接矩阵构建图
class vertex //构建自定义的顶点
{
public:
	vertex(string label)
	{
		this->label = label;
	}

public:
	string label;
	bool isvisted = false;
};

class graph
{
public:
	graph();
	~graph();
	void add_vertex(string label);
	void add_edge(int start, int end);
	void printmatrix();
	void showvertex(int a);

	void DFS(); //深度优先搜索
	void BFS(); //广度优先搜索

private:
	vertex *vertexlist[max_verts];
	int nverts; //图中当前的节点数
	int adjmat[max_verts][max_verts]; //邻接矩阵
	int getadj_next_unvisited_vertex(int v); //找到当前顶点的下一个邻接顶点
};

void graph::BFS()
{
	queue<int> myqueue; //保存顶点的下标
	vertexlist[0]->isvisted = true;
	showvertex(0);
	myqueue.push(0);//访问过的每一个节点都要放入队列
	int v1;
	while (myqueue.size() > 0)
	{
		v1 = myqueue.front();//返回队头元素
		myqueue.pop();		 //出队
		int v2 = getadj_next_unvisited_vertex(v1);
		while (v2 != -1)
		{
			vertexlist[v2]->isvisted = true;
			showvertex(v2);
			myqueue.push(v2);
			v2 = getadj_next_unvisited_vertex(v1); //继续找v1的其他邻接点，此时v2已经置为true，不会重复找到刚才的v2
		}
	}
	cout << endl;

	for (int i = 0; i < nverts; i++)
	{
		vertexlist[i]->isvisted = false; //将访问过的节点全部变为未访问，以便下一次广度优先搜索
	}
}

void graph::DFS()
{
	stack<int> mystack; //保存顶点的下标
	vertexlist[0]->isvisted = true;
	showvertex(0);
	mystack.push(0);

	int v;
	while (mystack.size() > 0)
	{
		v = getadj_next_unvisited_vertex(mystack.top());
		if (v == -1)
			mystack.pop();
		else
		{
			vertexlist[v]->isvisted = true;
			showvertex(v);
			mystack.push(v);
		}
	}
	cout << endl;
	for (int i = 0; i < nverts; i++)
	{
		vertexlist[i]->isvisted = false;
	}
}

int graph::getadj_next_unvisited_vertex(int v)
{
	for (int i = 0; i < nverts; i++)
	{
		if ((adjmat[v][i] == 1) && (vertexlist[i]->isvisted == false))
			return i;
	}
	return -1;
}

void graph::showvertex(int a)
{
	cout << vertexlist[a]->label << " ";
}

graph::graph()
{
	nverts = 0;
	for (int i = 0; i < max_verts; i++)
	{
		for (int j = 0; j < max_verts; j++)
		{
			adjmat[i][j] = 0;
		}
	}
}

graph::~graph()
{
	for (int i = 0; i < nverts; i++)
	{
		delete vertexlist[i];
	}
}

void graph::add_vertex(string label)
{
	vertex *myvertex = new vertex(label);
	vertexlist[nverts++] = myvertex;
}

void graph::add_edge(int start, int end)
{
	adjmat[start][end] = 1;
	adjmat[end][start] = 1;
}

void graph::printmatrix()
{
	for (int i = 0; i < nverts; i++)
	{
		for (int j = 0; j < nverts; j++)
		{
			cout << adjmat[i][j] << " ";
			cout << endl;
		}
	}
}

int main() 
{
	graph mygraph;
	mygraph.add_vertex("lebron");
	mygraph.add_vertex("AD");
	mygraph.add_vertex("kwai");
	mygraph.add_vertex("kuzima");
	mygraph.add_vertex("green");
	mygraph.add_vertex("langduo");
	mygraph.add_edge(0, 1);
	mygraph.add_edge(0, 2);
	mygraph.add_edge(0, 3);
	mygraph.add_edge(1, 5);
	mygraph.add_edge(2, 4);
	mygraph.BFS();
	cout << "-------------------" << endl;
	mygraph.DFS();

	system("pause");
	return 0;
}
