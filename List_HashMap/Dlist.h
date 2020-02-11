#pragma once
 /*Desc: linux内核源码双向链表实现include / linux / list.h*/

//双向链表节点
struct list_head
{
	struct list_head *next, *prev;
};

//初始化节点：设置name节点的前继节点和后继节点都是指向name本身
#define LIST_HEAD_INIT(name) {&(name), &(name)}
static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

//添加节点，将new插入到prev和next之间
static inline void __list_add(struct list_head *newlist, 
							  struct list_head *prev, 
							  struct list_head *next)
{
	next->prev = newlist;
	newlist->next = next;
	newlist->prev = prev;
	prev->next = newlist;
}
//将newlist添加到head之后
static inline void list_add(struct list_head *newlist, struct list_head *head)
{
	__list_add(newlist, head, head->next);
}
//将newlist添加到head之前 即将new添加到双链表的末尾。
static inline void list_add_tail(struct list_head *newlist, struct list_head *head)
{
	__list_add(newlist, head->prev, head);
}

//从双链表中删除entry节点
static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}
static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}
//从双链表中删除entry节点 并将entry节点的前继节点和后继节点都指向entry本身
static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

//用新节点取代旧节点
static inline void list_replace(struct list_head *old, struct list_head *newlist)
{
	newlist->next = old->next;
	newlist->next->prev = newlist;
	newlist->prev = old->prev;
	newlist->prev->next = newlist;
}

//双链表为空
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

//获取"MEMBER成员"在"结构体TYPE"中的位置偏移
#define offsetoff(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
// 根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来获取指向整个结构体变量的指针
#define container(ptr, type, member) ((type *)((char *)ptr - offsetoff(type, member)))

//遍历双向链表
#define list_for_each(pos, head) \
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
	for(pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_entry(ptr, type, member) \
	container(ptr, type, member)
