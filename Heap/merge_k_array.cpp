#include <vector>
#include <queue>
#include <iostream>
#include <limits.h>

using namespace std;

//定义最小堆节点
struct MinHeapNode
{
	int val; //待比较元素
	int i;   //数组索引
	int j;	 //该数组下一个元素的索引（判断元素是否用完）
	MinHeapNode(int a, int b, int c) :val(a), i(b), j(c) {}
};

struct cmp
{
	bool operator()(const MinHeapNode& m1, const MinHeapNode& m2)const
	{
		return m1.val > m2.val;
	}
};

vector<int>mergeKarray(vector<vector<int>>&nums)
{
	vector<int>res;
	priority_queue<MinHeapNode, vector<MinHeapNode>, cmp> pq; //小顶堆 优先级队列

	//将每个一维数组中的第一个元素放入队列中（并排序）
	int numcounts = 0;//总元素的个数
	for (int i = 0; i < nums.size(); i++)
	{
		pq.push(MinHeapNode(nums[i][0], i, 1));
		numcounts += nums[i].size();
	}
	
	while (res.size() < numcounts)
	{
		MinHeapNode tmp = pq.top();				//队头元素为最小 
		pq.pop();								//弹出队头元素
		res.push_back(tmp.val);					//将这个最小元素放入新的数组中
		if (tmp.j < nums[tmp.i].size())			//设置j=1  该数组下一个元素的索引（判断元素是否用完,用完的话可以不做处理，也可										以设置堆顶元素为最大值） 
		{
			tmp.val = nums[tmp.i][tmp.j];       //取该数组的下一个元素
			tmp.j++;
			//pq.push(tmp);						//放入队列中继续比较
		}
		else
		{
			tmp.val = INT_MAX;
		}
		pq.push(tmp);						//放入队列中继续比较
	}
	return res;
}





int main()
{
	vector<vector<int>>nums;
	nums.push_back({ 1, 3, 6, 9, 10 });
	nums.push_back({ -1, 2, 4, 5,12 });
	nums.push_back({ -4, 1, 7, 15, 22 });
	nums.push_back({ -8, 0, 3, 4, 15 });
	vector<int>res = mergeKarray(nums);

	/*for(auto a:b)中b为一个容器，效果是利用a遍历并获得b容器中的每一个值，但是a无法影响到b容器中的元素。
	  for(auto &a:b)中加了引用符号，可以对容器中的内容进行赋值，即可通过对a赋值来做到容器b的内容填充。*/
	for (auto i : res)
		cout << i << " ";

	system("pause");
	return 0;
}