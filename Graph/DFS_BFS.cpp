#include <iostream>
#include <string>
#include <stack>
#include <queue>

//������� (ʹ��ջ����ݹ����)
//������ȣ�ʹ�ö��У�

#define max_verts 10

using namespace std;

//�ڽӾ��󹹽�ͼ
class vertex //�����Զ���Ķ���
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

	void DFS(); //�����������
	void BFS(); //�����������

private:
	vertex *vertexlist[max_verts];
	int nverts; //ͼ�е�ǰ�Ľڵ���
	int adjmat[max_verts][max_verts]; //�ڽӾ���
	int getadj_next_unvisited_vertex(int v); //�ҵ���ǰ�������һ���ڽӶ���
};

void graph::BFS()
{
	queue<int> myqueue; //���涥����±�
	vertexlist[0]->isvisted = true;
	showvertex(0);
	myqueue.push(0);//���ʹ���ÿһ���ڵ㶼Ҫ�������
	int v1;
	while (myqueue.size() > 0)
	{
		v1 = myqueue.front();//���ض�ͷԪ��
		myqueue.pop();		 //����
		int v2 = getadj_next_unvisited_vertex(v1);
		while (v2 != -1)
		{
			vertexlist[v2]->isvisted = true;
			showvertex(v2);
			myqueue.push(v2);
			v2 = getadj_next_unvisited_vertex(v1); //������v1�������ڽӵ㣬��ʱv2�Ѿ���Ϊtrue�������ظ��ҵ��ղŵ�v2
		}
	}
	cout << endl;

	for (int i = 0; i < nverts; i++)
	{
		vertexlist[i]->isvisted = false; //�����ʹ��Ľڵ�ȫ����Ϊδ���ʣ��Ա���һ�ι����������
	}
}

void graph::DFS()
{
	stack<int> mystack; //���涥����±�
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
