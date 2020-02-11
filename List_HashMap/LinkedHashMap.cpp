#define _CRT_SECURE_NO_WARNINGS
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "Dlist.h"
#include "LinkedHashMap.h"


LinkedHashMap *LinkedHashMap_create(int size, int nel_max,
	hash_value_func hash_value, keycmp_func keycmp, hash_node_free_func hash_node_free)
{
	int i = 0;
	LinkedHashMap *h = NULL;
	if ((size <= 0) || (hash_value == NULL) || (keycmp == NULL))
	{
		return NULL;
	}

	h = (LinkedHashMap *)malloc(sizeof(LinkedHashMap));
	if (h == NULL)
		return NULL;

	h->hTabs = (ListedHashMapNode**)malloc(sizeof(ListedHashMapNode*)*size);
	if (h->hTabs == NULL)
		return NULL;

	h->size = size;
	h->nel = 0;
	h->nel_max = nel_max;
	h->hash_value = hash_value;
	h->keycmp = keycmp;
	h->hash_node_free = hash_node_free;

	for (i = 0; i < size; i++)
	{
		h->hTabs[i] = NULL;
	}

	INIT_LIST_HEAD(&(h->header));

	return h;
}

void LinkedHashMap_destory(LinkedHashMap *h)
{
	struct list_head *pos = NULL;
	struct list_head *next = NULL;
	ListedHashMapNode *ptmp = NULL;

	if (h == NULL)
		return;

	list_for_each_safe(pos, next, &h->header)
	{
		ptmp = container(pos, ListedHashMapNode, Dlist_node);
		//��˫��������ɾ��
		list_del_init(pos);
		if (h->hash_node_free != NULL)
			h->hash_node_free(ptmp, 1);
	}

	free(h->hTabs);
	free(h);

	return;
}

int LinkedHashMap_insert(LinkedHashMap *h, void *key, void *data)
{
	int i = 0;
	int hPos = 0; 
	struct list_head *pos = NULL;
	ListedHashMapNode *cur = NULL;
	ListedHashMapNode *prev = NULL;

	hPos = h->hash_value(h, key); //���ݹ�ϣ������������������±�
	cur = h->hTabs[hPos];

	//��������
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0))
	{
		prev = cur;
		cur = cur->next;//����cur->next��NULL
	}

	if (cur == NULL)
	{
		/*����ڵ���ʱ��ȡ��ͷ�ڵ㣬�ӵ�ǰ��ϣ���˫�������ж�ɾ��*/
		if (h->nel_max == h->nel)
		{
			cur = LinkedHashMap_delete(h, list_entry(h->header.next, ListedHashMapNode, Dlist_node)->key);
			assert(cur != NULL);
			h->hash_node_free(cur, 0);
		}
		else/*������ʱ�������µĽڵ�*/
		{
			cur = (ListedHashMapNode*)malloc(sizeof(ListedHashMapNode));
			if (cur == NULL)
				return 1;
		}
		/*���뵽hashͰ��*/
		if (prev == NULL)//ɢ�б��еĵ�һ���ڵ�
		{
			cur->next = h->hTabs[hPos];
			h->hTabs[hPos] = cur;
		}
		else
		{
			cur->next = prev->next;
			prev->next = cur;
		}
		h->nel++;
	}
	//else
	//{
	//	/*��˫��������ɾ��*/
	//	list_del_init(&(cur->Dlist_node));
	//	/*ֻɾ��key ��data���ڴ�*/
	//	h->hash_node_free(cur, 0);
	//}

	cur->key = key;
	cur->data = data;

	list_add_tail(&(cur->Dlist_node), &(h->header));

	return 0;
}

ListedHashMapNode * LinkedHashMap_delete(LinkedHashMap *h, void *key)
{
	int hPos = 0;
	struct list_head *pos = NULL;
	ListedHashMapNode *cur = NULL;
	ListedHashMapNode *prev = NULL;

	/*���ҵ�ǰ�ڵ�*/
	hPos = h->hash_value(h, key);
	cur = h->hTabs[hPos];
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0))
	{
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		return NULL;
	}

	/*�ӹ�ϣͰ��ɾ��*/
	if (prev == NULL)
	{
		h->hTabs[hPos] = cur->next;
	}
	else
	{
		prev->next = cur->next;
	}

	/*��˫��������ɾ��*/
	list_del_init(&(cur->Dlist_node));
	h->nel--;

	return cur;
}

void *LinkedHashMap_search(LinkedHashMap *h, void *key)
{
	int hPos = 0;
	ListedHashMapNode *cur = NULL;

	/*���ҵ�ǰ�ڵ�*/
	hPos = h->hash_value(h, key);
	cur = h->hTabs[hPos];
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0))
	{
		cur = cur->next;
	}

	if (cur == NULL)
	{
		return NULL;
	}

	/*��˫��������ɾ���ڵ㣬����β��*/ 
	//if (h->header.prev != &(cur->Dlist_node))
	//{
	//	list_del_init(&(cur->Dlist_node));
	//	list_add_tail(&(cur->Dlist_node), &(h->header));
	//}

	return cur->data;
}

void LinkedHashMap__dump(LinkedHashMap *h)
{
	int i = 0;
	ListedHashMapNode * cur = NULL;
	struct list_head *pos = NULL;

	if (h == NULL)
	{
		return;
	}

	printf("\r\n----��ʼ--size[%d],nel[%d]------------", h->size, h->nel);
	for (i = 0; i < h->size; i++)
	{
		printf("\r\n htables[%d]:", i);
		cur = h->hTabs[i];
		while ((cur != NULL))
		{
			printf("key[%s],data[%s] ", cur->key, cur->data);
			cur = cur->next;
		}
	}

	printf("\r\n--------------------------------------------------------\r\n");

	list_for_each(pos, &(h->header))
	{
		cur = list_entry(pos, ListedHashMapNode, Dlist_node);
		printf("key[%s] ", cur->key);

	}

	printf("\r\n----����--size[%d],nel[%d]------------", h->size, h->nel);
}

struct test_node
{
	char key[80];
	char data[80];
};

//��ϣ����
unsigned int siample_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while (*str)
	{
		hash = hash*seed + *str++;
	}

	return hash & (0x7FFFFFFF);
}

int hashtab_hvalue(LinkedHashMap *h, const void *key)
{
	return (siample_hash((char *)key) % h->size);
}


int hashtab_keycmp(LinkedHashMap *h, const void *key1, const void *key2)
{
	return strcmp((char*)key1, (char*)key2);
}

void hashtab_node_free(ListedHashMapNode *node, int flg)
{
	struct test_node * ptmp = NULL;

	ptmp = list_entry(node->key, struct test_node, key);

	free(ptmp);
	if (flg)
	{
		free(node);
	}
}

int main()
{
	int i = 0;
	int res = 0;
	char *pres = NULL;
	ListedHashMapNode *node = NULL;
	struct test_node *p = NULL;
	LinkedHashMap *h = NULL;
	
	h = LinkedHashMap_create(3, 6, hashtab_hvalue, hashtab_keycmp, hashtab_node_free);
	assert(h != NULL);
	
	while (1)
	{
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n ������key �� value�������Ե���\"quit\"ʱ�˳�");
		scanf("%s", p->key);
		scanf("%s", p->data);

		if (strcmp(p->key, "quit") == 0)
		{
			free(p);
			break;
		}

		res = LinkedHashMap_insert(h, p->key, p->data);
		if (res != 0)
		{
			free(p);
			printf("\r\n key[%s],data[%s] insert failed %d", p->key, p->data, res);
		}
		else
		{
			printf("\r\n key[%s],data[%s] insert success %d", p->key, p->data, res);
		}
		LinkedHashMap__dump(h);
	}

	while (1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n ������key ��ѯvalue����ֵ�������Ե���\"quit\"ʱ�˳�");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0)
		{
			free(p);
			break;
		}

		pres = (char*)LinkedHashMap_search(h, p->key);
		if (pres == NULL)
		{
			printf("\r\n key[%s] search data failed", p->key);
		}
		else
		{
			printf("\r\n key[%s],search data[%s] success", p->key, pres);
		}
		free(p);
		LinkedHashMap__dump(h);
	}

	while (1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n ������key ɾ���ڵ����ֵ�������Ե���\"quit\"ʱ�˳�");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0)
		{
			free(p);
			break;
		}
		node = LinkedHashMap_delete(h, p->key);
		if (node == NULL)
		{
			printf("\r\n key[%s] delete node failed ", p->key);
		}
		else
		{
			printf("\r\n key[%s],delete data[%s] success", node->key, node->data);
			h->hash_node_free(node, 1);
		}
		free(p);
		LinkedHashMap__dump(h);
	}

	LinkedHashMap_destory(h);

	return 0;
}