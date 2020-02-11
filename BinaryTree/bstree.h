#pragma once


typedef int mytype;

typedef struct _bstree_node
{
	mytype data;
	struct _bstree_node *lchild;
	struct _bstree_node *rchild;
}bstree_node;

typedef struct _bstree
{
	int size;
	int(*compare)(mytype key1, mytype key2);
	bstree_node *root;
}bstree;

typedef int(*compare_fuc)(mytype key1, mytype key2);


#define bstree_is_empty(tree)  (tree->size == 0)

bstree *bstree_create(compare_fuc compare);