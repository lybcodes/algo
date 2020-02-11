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
	//��ȡhash���������������ֵ
	hvalue = h->hash_value(h, key);//�±�key������ϣ�����ļ���õ�hvalue
	cur = h->htables[hvalue];//��һ��cur�ǿյģ���ΪҪ���������ڵ���ڴ滹û�з��䣬�����ֱ������86��
	
	//����������β�����½ڵ����
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) > 0))
	{
		prev = cur;
		cur = cur->next;//����cur->next��NULL
	}
	//���key�͵�ǰkey�ȶ�һ�£�ֱ�ӷ��أ������Ѿ�����
	if ((cur != NULL) && (h->keycmp(h, key, cur->key) == 0))
		return 2;

	newnode = (hashtab_node *)malloc(sizeof(hashtab_node));
	if (newnode == NULL)
		return 3;

	newnode->key = key;
	newnode->data = data;
	if (prev == NULL)//�����еĵ�һ���ڵ�
	{
		newnode->next = h->htables[hvalue];//����Ϊ�գ�����nextָ��ָ��NULL
		h->htables[hvalue] = newnode;//���´����Ľڵ�ŵ�������
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
	//����
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

	printf("\r\n---��ʼ--size[%d], nel[%d]---------", h->size, h->nel);
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
	printf("\r\n---����---size[%d], nel[%d]--------", h->size, h->nel);
}

struct test_node
{
	char key[80];
	char data[80];
};


/*�ַ���ת��Ϊ���εĺ���(���ĵ�˼����ͨ��һ��ѡ����������Ҳ��Ϊ����(seed)��ͨ��ѡ������Ӧ����һ����������31�� 131��1313�ȣ������ĺô����ڼ��ٲ�ͬ�ַ���ӳ��Ϊ��ͬ�����ĳ�ͻ��ͨ��һ�����㹫ʽ������ͬ���ַ�������ת��Ϊ����)
*/
unsigned int sample_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while (*str)
	{
		//ÿת��һλ�ַ����õ�ǰ��hashֵ����seed�ټ����ַ���ASCLL��
		//hash *seed�������Ϊ��ǰ�ַ�����ǰһ���ַ���hashֵ�Ļ����ϣ�ƫ����һ�����ӵľ���
		hash = hash *seed + *str++;
	}
	return hash & (0x7fffffff); /*ÿ��ʮ��������4bit�����8λ16������4���ֽڣ��պ���һ��int���� F�Ķ�������Ϊ 1111 7�Ķ�������Ϊ 0111 ����һ������������ 0x7FFFFFFF �Ķ����Ʊ�ʾ���ǳ�����λ�� 0�����඼��1 ����˵���������������� int����Ϊ��һλ�Ƿ���λ��0 ��ʾ��������������ֹ�����±���ָ���*/
}

int hashtab_hvalue(hashtab *h, const void *key)
{
	return (sample_hash((char *)key) % h->size);//����c++��˵void*��char*������ʾת��
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
		printf("\r\n ������key �� value�������Ե���\"quit\"ʱ�˳�\n");
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
		printf("\r\n ������key ɾ���ڵ����ֵ�� �����Ե���\"quit\"ʱ�˳�\n");
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