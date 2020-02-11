#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./list_queue.h"

/*创建队列头*/
list_queue *list_queue_create()
{
	list_queue *queue = NULL;
	queue = (list_queue *)malloc(sizeof(list_queue));
	if (queue == NULL) return NULL;

	queue->num = 0;
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

int list_queue_enqueue(list_queue *queue, void *data)
{
	queue_node *ptmp = NULL;

	if (queue == NULL) return -1;

	ptmp = (queue_node *)malloc(sizeof(queue_node));
	if (ptmp == NULL) return -1;

	ptmp->data = data;
	ptmp->next = NULL;
	if (queue->head == NULL)
		queue->head = ptmp;
	else
		queue->tail->next = ptmp; //插到队列尾
	queue->tail = ptmp;           //新插入尾部的节点成为尾节点
	queue->num++;

	return 0;
}

//这里之所以会传二级指针 是因为函数内部会修改void*data的值，所以要传它的指针也就是二级指针
int list_queue_dequeue(list_queue *queue, void **data)
{
	queue_node *ptmp = NULL;
	if ((queue == NULL) || (data == NULL) || list_queue_is_empty(queue))
	{
		return -1;
	}

	*data = queue->head->data; //接受出队的数据
	ptmp = queue->head;
	queue->head = queue->head->next;
	queue->num--;

	if (queue->head == NULL)
		queue->tail = NULL;

	free(ptmp);
	return 0;
}