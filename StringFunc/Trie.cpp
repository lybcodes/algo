/****************************
�ֵ���ʵ�֣�����a-z26����ĸ
******************************/

#include <iostream>
#include <string>

using namespace std;

class TrieNode
{
public:
	char data;
	bool is_ending_char;
	TrieNode *children[26];

	TrieNode(char ch)
	{
		data = ch;
		is_ending_char = false;
		for (int i = 0; i < 26; i++)
			children[i] = NULL;
	}
};

class Trie
{
private:
	TrieNode *root;
public:
	Trie()
	{
		root = new TrieNode('/'); //���ڵ㲻������
	}

	//�������Ĺ��̾�������������ַ���
	void insert_string(const char str[])
	{
		TrieNode *cur = root;
		for (unsigned int i = 0; i < strlen(str); i++)
		{
			int index = int(str[i] - 'a'); //���ַ��� ASCII ���ȥ 'a' �� ASCII ������Ϊ���������е��±�
			if (cur->children[index] == NULL)
			{
				TrieNode *temp = new TrieNode(str[i]);
				cur->children[index] = temp;
			}
			cur = cur->children[index]; //�ڵ㲻Ϊ�� �ʹ浽�����ӽڵ�
		}
		cur->is_ending_char = true; //�ַ��������֮�󽫱�־λ��Ϊtrue
	}

	//���ֵ����в���һ���ַ���
	bool search_string(const char str[])
	{
		TrieNode *cur = root;
		for (unsigned int i = 0; i < strlen(str); i++)
		{
			int index = int(str[i] - 'a');
			if (cur->children[index] == NULL)
			{
				return false;
			}
			cur = cur->children[index];
		}
		if (cur->is_ending_char == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#if 0
int main()
{
	char str[][8] = { "how", "hi", "her", "hello", "so", "see", "however" };

	Trie test;
	for (int i = 0; i < 7; i++)
	{
		test.insert_string(str[i]);
	}

	cout << "Finding \'her\':" << test.search_string("her") << endl;
	cout << "Finding \'he\':" << test.search_string("he") << endl;
	cout << "Finding \'hello\':" << test.search_string("hello") << endl;
	cout << "Finding \'howeve\':" << test.search_string("howeve") << endl;

	system("pause");
	return 0;
}

#endif