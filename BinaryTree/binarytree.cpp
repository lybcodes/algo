#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include"list_queue.h"

typedef struct treenode
{
	int data;
	int count;//������ �ں�������У������ĸ��ڵ��ڵ�һ�α�����ʱ�򲻻������ֻ���ڵڶ��α�����ʱ������
	struct treenode *lchild;
	struct treenode *rchild;
}Tnode, Tree;

//����һ�����������͵�ַ��ջ�����������ʱ��׷�ٵ����ĵ�ַ
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
Tree *pop()//ȡջ������ջ��
{
	return s.elements[--s.top];
}
int empty()
{
	return s.top == 0;
}


//���ﴫ�ݶ���ָ������Ϊ*Root = (Tnode *)malloc(sizeof(Tnode));�����ڲ����޸�һ��ָ���ֵ
void binarytree_create(Tree **Root)
{
	int a = 0;
	printf("\r\n ����ڵ���ֵ��������Ϊ100ʱ����ǰ�ڵ㴴����ɣ�:");//�ݹ���ֹ����
	scanf("%d", &a);

	if (a == 100) *Root = NULL;
	else
	{
		*Root = (Tnode *)malloc(sizeof(Tnode));
		if (*Root == NULL) return ;

		(*Root)->data = a;
		printf("\r\n ���� %d �����ӣ�", a);
		binarytree_create(&((*Root)->lchild));
		printf("\r\n ���� %d ���Һ��ӣ�", a);
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

/*ǰ��ݹ����:�����--��������---��������*/
void binarytree_preorder(Tree *root)
{
	if (root == NULL) return;

	printf(" %d ", root->data);
	binarytree_preorder(root->lchild);
	binarytree_preorder(root->rchild);
	return;
}
/*ǰ��ǵݹ����:�����--��������---��������*/
void preorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL) //�ȱ������Ӳ����
		{
			printf(" %d ", tmp->data);
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0)//�����ӱ������ȡջ�������Һ��� ��ʱѭ����û�н������ٱ����������ӣ�ֱ������ȫ������������
		{
			tmp = pop();
			tmp = tmp->rchild;
		}
	}
	printf("\n");
}

/*����ݹ����:������--�����ڵ�---��������*/
void binarytree_inorder(Tree *root)
{
	if (root == NULL) return;

	binarytree_inorder(root->lchild);
	printf(" %d  ", root->data);
	binarytree_inorder(root->rchild);
	return;
}
/*����ǵݹ����:������--�����ڵ�---��������*/
void inorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL) //�Ȱ�����������ջ
		{
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0) //������ջ����	ȡջ�����ջ��Ԫ�� �����Һ���
		{
			tmp = pop();
			printf(" %d ", tmp->data);
			tmp = tmp->rchild;
		}
	}
	printf("\n");
}

/*����ݹ����:������---��������-�����ڵ�*/
void binarytree_postorder(Tree *root)
{
	if (root == NULL) return;
	binarytree_postorder(root->lchild);
	binarytree_postorder(root->rchild);
	printf(" %d ", root->data);
	return;
}
/*����ǵݹ����:������---��������-�����ڵ�*/
void postorder(Tree *root)
{
	Tree *tmp = root;
	while (tmp != NULL || s.top != 0)
	{
		while (tmp != NULL)
		{
			tmp->count = 1; //��ǰ�ڵ��״α�����
			push(tmp);
			tmp = tmp->lchild;
		}
		if (s.top != 0)
		{
			tmp = pop();
			if (tmp->count == 1) //��һ�γ�����ջ��
			{
				tmp->count++;
				push(tmp);
				tmp = tmp->rchild;
			}
			else if (tmp->count == 2)//�ڶ���������ÿգ���ֹ������ѭ��
			{
				printf(" %d ", tmp->data);
				tmp = NULL;
			}
		}
	}
	printf("\n");
}

//�������:��һ������ÿһ�����ϵ��¿�ʼ���δ����ұ������
void binarytree_levelorder(Tree *root)
{
	list_queue *queue = NULL;
	Tnode *node = NULL;
	if (root == NULL) return;

	queue = list_queue_create();

	//���ڵ������
	list_queue_enqueue(queue, (void *)root);

	while (!list_queue_is_empty(queue))
	{
		//list_queue_dequeue(queue,(void *)&node);//����д�ᱨ�� 
		list_queue_dequeue(queue, (void **)&node);
		printf(" %d ", node->data);

		if (node->lchild != NULL)
			list_queue_enqueue(queue, (void *)node->lchild);
		if (node->rchild != NULL)
			list_queue_enqueue(queue, (void *)node->rchild);
	}
	free(queue);
}


/*��ӡҶ�ӽڵ�*/
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

/*��ӡҶ�ӵĸ���*/
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

/*��ӡ���ĸ߶�*/
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

	printf("\r\n����������:");
	binarytree_create(&root);
	printf("\r\n�������������:");
	binarytree_preorder(root);
	printf("\r\n�������������:");
	binarytree_inorder(root);
	printf("\r\n�������������:");
	binarytree_postorder(root);
	printf("\r\n��α���������:");
	binarytree_levelorder(root);

	printf("\r\n��ӡ������Ҷ�ӽڵ�:");
	binarytree_printfleaf(root);
	printf("\r\n��ӡ������Ҷ�ӽڵ����:%d", binarytree_getleafnum(root));
	printf("\r\n��ӡ�������߶�:%d", binarytree_gethigh(root));

	binarytree_destory(root);

	system("pause");
	return 0;
}

#endif