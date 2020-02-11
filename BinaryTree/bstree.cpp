#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

bstree *bstree_create(compare_fuc compare)
{
	bstree *tree = NULL;
	tree = (bstree*)malloc(sizeof(bstree));
	if (tree == NULL) return NULL;

	tree->size = 0;
	tree->root = NULL;
	tree->compare = compare;
	return tree;
}

bstree_node *bstree_search(bstree *tree, mytype data)
{
	bstree_node *node = NULL;
	int res = 0;
	if (tree == NULL || bstree_is_empty(tree)) return NULL;

	node = tree->root;

	while (node != NULL)
	{
		res = tree->compare(data, node->data);
		if (res == 0)
			return node;  //�������0 ˵��Ҫ�ҵľ��ǵ�ǰ�ڵ�
		else if (res > 0)
			node = node->rchild; //����0 ˵�����ڵ�ǰ�ڵ� Ӧ����������
		else
			node = node->lchild;  
	}
	return NULL;
}

int bstree_insert(bstree *tree, mytype data)
{
	bstree_node *node = NULL;
	bstree_node *tmp = NULL;
	int res = 0;
	if (tree == NULL)
		return -1;
	node = (bstree_node *)malloc(sizeof(bstree_node));
	if (node == NULL)
		return -2;
	node->data = data;
	node->lchild = NULL;
	node->rchild = NULL;

	/*���������Ϊ�� ֱ�ӹҵ����ڵ�*/
	if (bstree_is_empty(tree))
	{
		tree->root = node;
		tree->size++;
		return 0;
	}

	tmp = tree->root;

	while (tmp != NULL)
	{
		res = tree->compare(data, tmp->data);
		if (res > 0)
		{
			if (tmp->rchild == NULL)
			{
				tmp->rchild = node;
				tree->size++;
				return 0;
			}
			tmp = tmp->rchild;
		}
		else 
		{
			if (tmp->lchild == NULL)
			{
				tmp->lchild = node;
				tree->size++;
				return 0;
			}
			tmp = tmp->lchild;
		}
	}
	//return -3;
}

int bstree_delete(bstree *tree, mytype data)
{
	bstree_node *node = NULL;        //Ҫɾ���Ľڵ�
	bstree_node *pnode = NULL;       //Ҫɾ���ڵ�ĸ��ڵ�
	bstree_node *minnode = NULL;     //Ҫɾ���ڵ�ĸ��ڵ�
	bstree_node *pminnode = NULL;    //Ҫɾ���ڵ�ĸ��ڵ�
	mytype tmp = 0;
	int res = 0;

	if ((tree == NULL) || (bstree_is_empty(tree)))
		return -1;
	node = tree->root;
	while ((node != NULL) && ((res = tree->compare(data, node->data)) != 0))
	{
		pnode = node;
		if (res > 0)
			node = node->rchild;
		else
			node = node->lchild;
	}


	/*Ҫɾ���Ľڵ㲻����*/
	if (node == NULL)
		return -2;

	/*1�����Ҫɾ��node��2���ӽڵ㣬��Ҫ�ҵ�����������С�ڵ�minnode��
		 ����minnode��node�ڵ����ݣ�����minnode�ڵ����Ҫɾ���Ľڵ�
		 �ٸ���node��pnode�ڵ�ָ��Ҫɾ���Ľڵ�*/
	if ((node->lchild != NULL) && (node->rchild != NULL))
	{
		minnode = node->rchild;
		pnode = node;

		while (minnode->lchild != NULL) //�ҵ�node�ڵ��������е���С�ڵ㣨С�����϶����������У�
		{
			pminnode = minnode;
			minnode = minnode->lchild;
		}
		/*node �ڵ��minnode�ڵ����ݻ���*/
		tmp = node->data;
		node->data = minnode->data;
		minnode->data = tmp;
		/*ɾ��minnode�ڵ�*//*����Ҫɾ���Ľڵ���丸�ڵ�*/
		node = minnode;
		pnode = pminnode;
	}

	/*2����ǰҪɾ���Ľڵ�ֻ�����ӻ����Һ���ʱ��ֱ�Ӹ��ڵ�ָ��ɾ���Ľڵ�*/
	if (node->lchild != NULL)
	{
		minnode = node->lchild;
	}
	else if (node->rchild != NULL)
	{
		minnode = node->rchild;
	}
	else
	{
		minnode = NULL; 
	}

	if (pnode == NULL) /*��Ҫɾ����ʱ���ڵ�ʱ,*/
	{
		tree->root = minnode;
	}
	//����Ĵ���ʵ��֮ǰ���������node�ڵ�ɾ��
	else if (pnode->lchild == node)
	{
		pnode->lchild = minnode;
	}
	else
	{
		pnode->rchild = minnode;
	}
	tree->size--;
	free(node);

	return 0;
}

/*���õݹ鷽ʽɾ���ڵ�*/
void bstree_destory_node(bstree *tree, bstree_node *root)
{
	if (root == NULL)
		return;

	bstree_destory_node(tree, root->lchild);
	bstree_destory_node(tree, root->rchild);
	free(root);
}
/*��������������*/
void bstree_destory(bstree *tree)
{
	bstree_destory_node(tree, tree->root);
	free(tree);
	return;
}

void bstree_inorder_node(bstree_node *root)
{
	bstree_node *node = NULL;
	if (root == NULL)
		return;

	bstree_inorder_node(root->lchild);
	printf(" %d ", root->data);
	bstree_inorder_node(root->rchild);
	return;
}

void bstree_dump(bstree *tree)
{
	bstree_node *node = NULL;
	if ((tree == NULL) || (bstree_is_empty(tree)))
	{
		printf("\r\n the tree is empty !");
	}
	printf("\r\n start---------%d---------\r\n", tree->size);
	bstree_inorder_node(tree->root);
	printf("\r\n end--------------------\r\n", tree->size);
}

int bstree_compare(mytype key1, mytype key2)
{
	if (key1 == key2)
		return 0;
	else if (key1 > key2)
		return 1;
	else
		return -1;
}


int main()
{
	bstree *tree = NULL;
	bstree_node *node = NULL;
	mytype data = 0;
	int res = 0;

	tree = bstree_create(bstree_compare);
	assert(tree != NULL);

	while (1)
	{
		printf("\r\n ����һ�����֣�����100ʱ�˳�:");
		scanf("%d", &data);
		if (data == 100) break;
		res = bstree_insert(tree, data);
		printf("\r\n %d ����%s�ɹ�", data, (res != 0) ? ("��") : (""));
	}
	bstree_dump(tree);

	while (1)
	{
		printf("\r\n ��ѯһ�����֣� ����100ʱ�˳�:");
		scanf("%d", &data);
		if (data == 100) break;
		node = bstree_search(tree, data);
		printf("\r\n %d %s����������", data, (node == NULL) ? ("��") : (""));
	}
	bstree_dump(tree);

	while (1)
	{
		printf("\r\n ɾ��һ������ ����100ʱ�˳�:");
		scanf("%d", &data);
		if (data == 100) break;
		res = bstree_delete(tree, data);
		printf("\r\n %d ɾ��%s�ɹ�", data, (res != 0) ? ("��") : (""));
		bstree_dump(tree);
	}

	bstree_destory(tree);

	system("pause");
	return 0;
}