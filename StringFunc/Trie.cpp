/****************************
字典树实现，包含a-z26个字母
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
		root = new TrieNode('/'); //根节点不存数据
	}

	//构建树的过程就是往里面添加字符串
	void insert_string(const char str[])
	{
		TrieNode *cur = root;
		for (unsigned int i = 0; i < strlen(str); i++)
		{
			int index = int(str[i] - 'a'); //拿字符的 ASCII 码减去 'a' 的 ASCII 码来作为其在数组中的下标
			if (cur->children[index] == NULL)
			{
				TrieNode *temp = new TrieNode(str[i]);
				cur->children[index] = temp;
			}
			cur = cur->children[index]; //节点不为空 就存到它的子节点
		}
		cur->is_ending_char = true; //字符串添加完之后将标志位置为true
	}

	//在字典树中查找一个字符串
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