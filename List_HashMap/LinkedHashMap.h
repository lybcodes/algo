#pragma once
#include "Dlist.h"
/*LRU缓存淘汰算法采用散列表和双向链表这两种数据结构组合实现*/

typedef struct _listed_hashmap_node
{
	void *key; //键
	void *data; //数据
	struct _listed_hashmap_node *next; //哈希冲突时 用来挂接后续节点
	struct list_head Dlist_node; //用来挂接双向链表(散列表中的元素用链表连起来)
}ListedHashMapNode;

typedef struct _listed_hashmap
{
	ListedHashMapNode **hTabs; //哈希桶
	struct list_head header; //双向循环链表头
	int size;    /*散列表元素个数*/
	int nel_max;/*链表支持最大节点数*/
	int nel;
	int (*hash_value)(struct _listed_hashmap *h, const void *key); //哈希函数
	int (*keycmp)(struct _listed_hashmap *h, const void *key1, const void *key2);
	void (*hash_node_free)(ListedHashMapNode *node, int flg); 
}LinkedHashMap;

typedef int(*hash_value_func)(struct _listed_hashmap *h, const void *key);
typedef int(*keycmp_func)(struct _listed_hashmap *h, const void *key1, const void *key2);
typedef void(*hash_node_free_func)(ListedHashMapNode *node, int flg);

ListedHashMapNode *LinkedHashMap_delete(LinkedHashMap *h, void *key);