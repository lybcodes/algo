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
			return node;  //如果返回0 说明要找的就是当前节点
		else if (res > 0)
			node = node->rchild; //大于0 说明大于当前节点 应该找右子树
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

	/*如果二叉树为空 直接挂到根节点*/
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
	bstree_node *node = NULL;        //要删除的节点
	bstree_node *pnode = NULL;       //要删除节点的父节点
	bstree_node *minnode = NULL;     //要删除节点的父节点
	bstree_node *pminnode = NULL;    //要删除节点的父节点
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


	/*要删除的节点不存在*/
	if (node == NULL)
		return -2;

	/*1、如果要删除node有2个子节点，需要找到右子树的最小节点minnode，
		 更新minnode和node节点数据，这样minnode节点就是要删除的节点
		 再更新node和pnode节点指向要删除的节点*/
	if ((node->lchild != NULL) && (node->rchild != NULL))
	{
		minnode = node->rchild;
		pnode = node;

		while (minnode->lchild != NULL) //找到node节点右子树中的最小节点（小的数肯定在左子树中）
		{
			pminnode = minnode;
			minnode = minnode->lchild;
		}
		/*node 节点和minnode节点数据互换*/
		tmp = node->data;
		node->data = minnode->data;
		minnode->data = tmp;
		/*删除minnode节点*//*更新要删除的节点和其父节点*/
		node = minnode;
		pnode = pminnode;
	}

	/*2、当前要删除的节点只有左孩子或者右孩子时，直接父节点指向删除的节点*/
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

	if (pnode == NULL) /*当要删除的时根节点时,*/
	{
		tree->root = minnode;
	}
	//下面的代码实现之前所有情况的node节点删除
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

/*采用递归方式删除节点*/
void bstree_destory_node(bstree *tree, bstree_node *root)
{
	if (root == NULL)
		return;

	bstree_destory_node(tree, root->lchild);
	bstree_destory_node(tree, root->rchild);
	free(root);
}
/*二叉搜索树销毁*/
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
		printf("\r\n 插入一个数字，输入100时退出:");
		scanf("%d", &data);
		if (data == 100) break;
		res = bstree_insert(tree, data);
		printf("\r\n %d 插入%s成功", data, (res != 0) ? ("不") : (""));
	}
	bstree_dump(tree);

	while (1)
	{
		printf("\r\n 查询一个数字， 输入100时退出:");
		scanf("%d", &data);
		if (data == 100) break;
		node = bstree_search(tree, data);
		printf("\r\n %d %s存在于树中", data, (node == NULL) ? ("不") : (""));
	}
	bstree_dump(tree);

	while (1)
	{
		printf("\r\n 删除一个数， 输入100时退出:");
		scanf("%d", &data);
		if (data == 100) break;
		res = bstree_delete(tree, data);
		printf("\r\n %d 删除%s成功", data, (res != 0) ? ("不") : (""));
		bstree_dump(tree);
	}

	bstree_destory(tree);

	system("pause");
	return 0;
}