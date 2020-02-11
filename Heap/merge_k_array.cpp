#include <vector>
#include <queue>
#include <iostream>
#include <limits.h>

using namespace std;

//������С�ѽڵ�
struct MinHeapNode
{
	int val; //���Ƚ�Ԫ��
	int i;   //��������
	int j;	 //��������һ��Ԫ�ص��������ж�Ԫ���Ƿ����꣩
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
	priority_queue<MinHeapNode, vector<MinHeapNode>, cmp> pq; //С���� ���ȼ�����

	//��ÿ��һά�����еĵ�һ��Ԫ�ط�������У�������
	int numcounts = 0;//��Ԫ�صĸ���
	for (int i = 0; i < nums.size(); i++)
	{
		pq.push(MinHeapNode(nums[i][0], i, 1));
		numcounts += nums[i].size();
	}
	
	while (res.size() < numcounts)
	{
		MinHeapNode tmp = pq.top();				//��ͷԪ��Ϊ��С 
		pq.pop();								//������ͷԪ��
		res.push_back(tmp.val);					//�������СԪ�ط����µ�������
		if (tmp.j < nums[tmp.i].size())			//����j=1  ��������һ��Ԫ�ص��������ж�Ԫ���Ƿ�����,����Ļ����Բ�������Ҳ��										�����öѶ�Ԫ��Ϊ���ֵ�� 
		{
			tmp.val = nums[tmp.i][tmp.j];       //ȡ���������һ��Ԫ��
			tmp.j++;
			//pq.push(tmp);						//��������м����Ƚ�
		}
		else
		{
			tmp.val = INT_MAX;
		}
		pq.push(tmp);						//��������м����Ƚ�
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

	/*for(auto a:b)��bΪһ��������Ч��������a���������b�����е�ÿһ��ֵ������a�޷�Ӱ�쵽b�����е�Ԫ�ء�
	  for(auto &a:b)�м������÷��ţ����Զ������е����ݽ��и�ֵ������ͨ����a��ֵ����������b��������䡣*/
	for (auto i : res)
		cout << i << " ";

	system("pause");
	return 0;
}