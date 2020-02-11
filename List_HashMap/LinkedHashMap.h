#pragma once
#include "Dlist.h"
/*LRU������̭�㷨����ɢ�б��˫���������������ݽṹ���ʵ��*/

typedef struct _listed_hashmap_node
{
	void *key; //��
	void *data; //����
	struct _listed_hashmap_node *next; //��ϣ��ͻʱ �����ҽӺ����ڵ�
	struct list_head Dlist_node; //�����ҽ�˫������(ɢ�б��е�Ԫ��������������)
}ListedHashMapNode;

typedef struct _listed_hashmap
{
	ListedHashMapNode **hTabs; //��ϣͰ
	struct list_head header; //˫��ѭ������ͷ
	int size;    /*ɢ�б�Ԫ�ظ���*/
	int nel_max;/*����֧�����ڵ���*/
	int nel;
	int (*hash_value)(struct _listed_hashmap *h, const void *key); //��ϣ����
	int (*keycmp)(struct _listed_hashmap *h, const void *key1, const void *key2);
	void (*hash_node_free)(ListedHashMapNode *node, int flg); 
}LinkedHashMap;

typedef int(*hash_value_func)(struct _listed_hashmap *h, const void *key);
typedef int(*keycmp_func)(struct _listed_hashmap *h, const void *key1, const void *key2);
typedef void(*hash_node_free_func)(ListedHashMapNode *node, int flg);

ListedHashMapNode *LinkedHashMap_delete(LinkedHashMap *h, void *key);