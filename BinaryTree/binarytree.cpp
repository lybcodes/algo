#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include"list_queue.h"

typedef struct treenode
{
	int data;
	int count;//计数用 在后序遍历中，子树的根节点在第一次遍历的时候不会输出，只有在第二次遍历的时候才输出
	struct treenode *lchild;
	struct treenode *rchild;
}Tnode, Tree;

//定义一个储存树类型地址的栈，方便遍历的时候追踪到树的地址
typedef struct stack
{
	Tree *elements[100];
	int top;
}my_stack; 
my_stack s;
void stack_init()
{
	s.top = 0;
}
void push(Tree *tmp)
{
	s.elements[s.top++] = tmp;
}
Tree *pop()//取栈顶并出栈顶
{
	return s.elements[--s.top];
}
int empty()
{
	return s.top == 0;
}


//这里传递二级指针是因为*Root = (Tnode *)malloc(sizeof(Tnode));函数内部会修改一级指针的值
void binarytree_create(Tree **Root)
{
	int a = 0;
	printf("\r\n 输入节点数值（当输入为100时，当前节点创建完成）:");//递归终止条件
	scanf("%d", &a);

	if (a == 100) *Root = NULL;
	else
	{
		*Root = (Tnode *)malloc(sizeof(Tnode));
		if (*Root == NULL) return ;

		(*Root)->data = a;
		printf("\r\n 创建 %d 的左孩子：", a);
		binarytree_create(&((*Root)->lchild));
		printf("\r\n 创建 %d 的右孩子：", a);
		binarytree_create(&((*Root)->rchild));
	}
	return ;
}

void binarytree_destory(Tree *root)
{
	if (root == NULL) return;

	binarytree_destory(root->lchild);
	binarytree_destory(root->rchild);
	free(root);
}

/*前序递归遍历:根结点--》左子树---》右子树*/
void binarytree_preorder(Tree *root)
{
	if (root == NULL) return;

	printf(" %d ", root->data);
	binarytree_preorder(root->lchild);
	binarytree_preorder(root->rchild);
	return;
}
/*前序非递归遍历:根结点--》左子树---》右子树*/
void preorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL) //先遍历左孩子并输出
		{
			printf(" %d ", tmp->data);
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0)//当左孩子遍历完后，取栈顶，找右孩子 此时循环还没有结束，再遍历它的左孩子，直至孩子全部遍历结束。
		{
			tmp = pop();
			tmp = tmp->rchild;
		}
	}
	printf("\n");
}

/*中序递归遍历:左子树--》跟节点---》右子树*/
void binarytree_inorder(Tree *root)
{
	if (root == NULL) return;

	binarytree_inorder(root->lchild);
	printf(" %d  ", root->data);
	binarytree_inorder(root->rchild);
	return;
}
/*中序非递归遍历:左子树--》跟节点---》右子树*/
void inorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL) //先把所有左孩子入栈
		{
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0) //左孩子入栈结束	取栈顶输出栈顶元素 遍历右孩子
		{
			tmp = pop();
			printf(" %d ", tmp->data);
			tmp = tmp->rchild;
		}
	}
	printf("\n");
}

/*后序递归遍历:左子树---》右子树-》根节点*/
void binarytree_postorder(Tree *root)
{
	if (root == NULL) return;
	binarytree_postorder(root->lchild);
	binarytree_postorder(root->rchild);
	printf(" %d ", root->data);
	return;
}
/*后序非递归遍历:左子树---》右子树-》根节点*/
void postorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL)
		{
			tmp->count = 1; //当前节点首次被访问
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0)
		{
			tmp = pop();
			if (tmp->count == 1) //第一次出现在栈顶
			{
				tmp->count++;
				push(tmp);
				tmp = tmp->rchild;
			}
			else if (tmp->count == 2)//第二次输出并置空，防止陷入死循环
			{
				printf(" %d ", tmp->data);
				tmp = NULL;
			}
		}
	}
	printf("\n");
}

//层序遍历:从一棵树的每一层由上到下开始依次从左到右遍历输出
void binarytree_levelorder(Tree *root)
{
	list_queue *queue = NULL;
	Tnode *node = NULL;
	if (root == NULL) return;

	queue = list_queue_create();

	//根节点先入队
	list_queue_enqueue(queue, (void *)root);

	while (!list_queue_is_empty(queue))
	{
		//list_queue_dequeue(queue,(void *)&node);//这种写会报错 
		list_queue_dequeue(queue, (void **)&node);
		printf(" %d ", node->data);

		if (node->lchild != NULL)
			list_queue_enqueue(queue, (void *)node->lchild);
		if (node->rchild != NULL)
			list_queue_enqueue(queue, (void *)node->rchild);
	}
	free(queue);
}


/*打印叶子节点*/
void binarytree_printfleaf(Tree *root)
{
	if (root == NULL)
	{
		return;
	}

	if ((root->lchild == NULL) && (root->rchild == NULL))
	{
		printf(" %d ", root->data);
	}
	else
	{
		binarytree_printfleaf(root->lchild);
		binarytree_printfleaf(root->rchild);
	}
}

/*打印叶子的个数*/
int binarytree_getleafnum(Tree*root)
{
	if (root == NULL)
	{
		return 0;
	}

	if ((root->lchild == NULL) && (root->rchild == NULL))
	{
		return 1;
	}

	return binarytree_getleafnum(root->lchild) + binarytree_getleafnum(root->rchild);

}

/*打印数的高度*/
int binarytree_gethigh(Tree *root)
{
	int lhigh = 0;
	int rhigh = 0;
	if (root == NULL) return 0;

	lhigh = binarytree_gethigh(root->lchild);
	rhigh = binarytree_gethigh(root->rchild);

	return ((lhigh > rhigh) ? (lhigh + 1) : (rhigh + 1));
}

#if 0

int main()
{
	Tree *root = NULL;

	printf("\r\n创建二叉树:");
	binarytree_create(&root);
	printf("\r\n先序遍历二叉树:");
	binarytree_preorder(root);
	printf("\r\n中序遍历二叉树:");
	binarytree_inorder(root);
	printf("\r\n后序遍历二叉树:");
	binarytree_postorder(root);
	printf("\r\n层次遍历二叉树:");
	binarytree_levelorder(root);

	printf("\r\n打印二叉树叶子节点:");
	binarytree_printfleaf(root);
	printf("\r\n打印二叉树叶子节点个数:%d", binarytree_getleafnum(root));
	printf("\r\n打印二叉树高度:%d", binarytree_gethigh(root));

	binarytree_destory(root);

	system("pause");
	return 0;
}

#endif