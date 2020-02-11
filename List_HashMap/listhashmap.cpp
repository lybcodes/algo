#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "listhashmap.h"

#if 0


hashtab *hashtab_create(int size, hash_key_func hash_value, keycmp_func keycmp, hash_node_free_func hash_node_free)
{
	hashtab *h = NULL;
	int i = 0;
	if ((size < 0) || (hash_value == NULL) || (keycmp == NULL))
	{
		return NULL;
	}

	h = (hashtab *)malloc(sizeof(hashtab));
	if (h == NULL)	return NULL;

	h->htables = (hashtab_node **)malloc(size * sizeof(hashtab_node*));
	if (h->htables == NULL)	return NULL;

	h->size = size;
	h->nel = 0;
	h->hash_value = hash_value;
	h->keycmp = keycmp;
	h->hash_node_free = hash_node_free;

	for (i = 0; i < size; i++)
		h->htables[i] = NULL;

	return h;
}

void hashtab_destory(hashtab *h)
{
	int i = 0;
	hashtab_node *cur = NULL;
	hashtab_node *tmp = NULL;

	if (h == NULL)
		return;

	for (i = 0; i < h->size; i++)
	{
		cur = h->htables[i];
		while (cur != NULL)
		{
			tmp = cur;
			cur = cur->next;
			h->hash_node_free(tmp);
		}
		h->htables[i] = NULL;
	}

	free(h->htables);
	free(h);
	return;
}

int hashtab_insert(hashtab *h, void *key, void *data)
{
	unsigned int hvalue = 0;
	int i = 0;
	hashtab_node *cur = NULL;
	hashtab_node *prev = NULL;
	hashtab_node *newnode = NULL;

	if ((h == NULL) || (key == NULL) || (data == NULL))
		return 1;
	//获取hash函数计算出来的数值
	hvalue = h->hash_value(h, key);//下标key经过哈希函数的计算得到hvalue
	cur = h->htables[hvalue];//第一次cur是空的，因为要插入的链表节点的内存还没有分配，这里会直接跳到86行
	
	//遍历到链表尾部将新节点插入
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) > 0))
	{
		prev = cur;
		cur = cur->next;//这里cur->next是NULL
	}
	//如果key和当前key比对一致，直接返回，数据已经存在
	if ((cur != NULL) && (h->keycmp(h, key, cur->key) == 0))
		return 2;

	newnode = (hashtab_node *)malloc(sizeof(hashtab_node));
	if (newnode == NULL)
		return 3;

	newnode->key = key;
	newnode->data = data;
	if (prev == NULL)//数组中的第一个节点
	{
		newnode->next = h->htables[hvalue];//这里为空，所以next指针指向NULL
		h->htables[hvalue] = newnode;//将新创建的节点放到数组中
	}
	else
	{
		newnode->next = prev->next;
		prev->next = newnode;
	}

	h->nel++;
	return 0;
}

hashtab_node *hashtab_delete(hashtab *h, void *key)
{
	int hvalue = 0;
	int i = 0;
	hashtab_node *cur = NULL;
	hashtab_node *prev = NULL;

	if ((h == NULL) || (key == NULL))
	{
		return NULL;
	}

	hvalue = h->hash_value(h, key);
	cur = h->htables[hvalue];

	while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0))
	{
		if (h->keycmp(h, key, cur->key) == 0)
		{
			if (prev == NULL)
			{
				h->htables[hvalue] = cur->next;
			}
			else
			{
				prev->next = cur->next;
			}
			return cur;
		}
		prev = cur;
		cur = cur->next;
	}
	return NULL;
}

void *hashtab_search(hashtab *h, void *key)
{
	int hvalue = 0;
	int i = 0;
	hashtab_node *cur = NULL;

	if ((h == NULL) || (key == NULL))
		return NULL;

	hvalue = h->hash_value(h, key);
	cur = h->htables[hvalue];
	//遍历
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0))
	{
		if (h->keycmp(h, key, cur->key) == 0)
			return cur->data;
		cur = cur->next;
	}
	return NULL;
}

void hashtab_dump(hashtab *h)
{
	int i = 0;
	hashtab_node *cur = NULL;
	if (h == NULL) return;

	printf("\r\n---开始--size[%d], nel[%d]---------", h->size, h->nel);
	for (i = 0; i < h->size; i++)
	{
		printf("\r\n htables[%d] : ", i);
		cur = h->htables[i];
		while (cur != NULL)
		{
			printf("key[%s], data[%s] ", (char *)cur->key, (char *)cur->data);
			cur = cur->next;
		}
	}
	printf("\r\n---结束---size[%d], nel[%d]--------", h->size, h->nel);
}

struct test_node
{
	char key[80];
	char data[80];
};


/*字符串转化为整形的函数(核心的思想是通过一个选择器，我们也成为种子(seed)，通常选择种子应该是一个质数，如31， 131，1313等，这样的好处在于减少不同字符串映射为相同整数的冲突。通过一个计算公式，将不同的字符串进行转化为数字)
*/
unsigned int sample_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while (*str)
	{
		//每转换一位字符，用当前的hash值乘上seed再加上字符的ASCLL码
		//hash *seed可以理解为当前字符串再前一个字符串hash值的基础上，偏移了一个种子的距离
		hash = hash *seed + *str++;
	}
	return hash & (0x7fffffff); /*每个十六进制数4bit，因此8位16进制是4个字节，刚好是一个int整型 F的二进制码为 1111 7的二进制码为 0111 这样一来，整个整数 0x7FFFFFFF 的二进制表示就是除了首位是 0，其余都是1 就是说，这是最大的整型数 int（因为第一位是符号位，0 表示他是正数），防止数组下标出现负数*/
}

int hashtab_hvalue(hashtab *h, const void *key)
{
	return (sample_hash((char *)key) % h->size);//对于c++来说void*和char*必须显示转换
}

int hashtab_keycmp(hashtab *h, const void *key1, const void *key2)
{
	return strcmp((char *)key1, (char *)key2);
}

void hashtab_node_free(hashtab_node *node)
{
	struct test_node *ptmp = NULL;
	ptmp = container(node->key, struct test_node, key);
	free(ptmp);
	free(node);
}

int main()
{
	int i = 0;
	int res = 0;
	char *pres = NULL;
	hashtab_node *node = NULL;
	struct test_node *p = NULL;
	hashtab *h = NULL;

	h = hashtab_create(5, hashtab_hvalue, hashtab_keycmp, hashtab_node_free);
	assert(h != NULL);
	while (1)
	{
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 和 value，当可以等于\"quit\"时退出\n");
		scanf("%s", p->key);
		scanf("%s", p->data);

		if (strcmp(p->key, "quit") == 0)
		{
			free(p);
			break;
		}

		res = hashtab_insert(h, p->key, p->data);
		if (res != 0)
		{
			free(p);
			printf("\r\n key[%s], data[%s] insert failed %d", p->key, p->data, res);
		}
		else
			printf("\r\n key[%s], data[%s] insert success %d", p->key, p->data, res);
	}

	hashtab_dump(h);

	while (1)
	{
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 删除节点的数值， 当可以等于\"quit\"时退出\n");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0)
		{
			free(p);
			break;
		}
		node = hashtab_delete(h, p->key);
		if (node == NULL)
			printf("\r\n key[%s] delete node failed", p->key);
		else
		{
			printf("\r\n key[%s], delete data[%s] success", node->key, node->data);
			h->hash_node_free(node);
		}
		free(p);
		hashtab_dump(h);
	}

	hashtab_destory(h);

	return 0;
}

#endif