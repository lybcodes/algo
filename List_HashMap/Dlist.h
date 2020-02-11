#pragma once
 /*Desc: linux�ں�Դ��˫������ʵ��include / linux / list.h*/

//˫������ڵ�
struct list_head
{
	struct list_head *next, *prev;
};

//��ʼ���ڵ㣺����name�ڵ��ǰ�̽ڵ�ͺ�̽ڵ㶼��ָ��name����
#define LIST_HEAD_INIT(name) {&(name), &(name)}
static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

//��ӽڵ㣬��new���뵽prev��next֮��
static inline void __list_add(struct list_head *newlist, 
							  struct list_head *prev, 
							  struct list_head *next)
{
	next->prev = newlist;
	newlist->next = next;
	newlist->prev = prev;
	prev->next = newlist;
}
//��newlist��ӵ�head֮��
static inline void list_add(struct list_head *newlist, struct list_head *head)
{
	__list_add(newlist, head, head->next);
}
//��newlist��ӵ�head֮ǰ ����new��ӵ�˫�����ĩβ��
static inline void list_add_tail(struct list_head *newlist, struct list_head *head)
{
	__list_add(newlist, head->prev, head);
}

//��˫������ɾ��entry�ڵ�
static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}
static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}
//��˫������ɾ��entry�ڵ� ����entry�ڵ��ǰ�̽ڵ�ͺ�̽ڵ㶼ָ��entry����
static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

//���½ڵ�ȡ���ɽڵ�
static inline void list_replace(struct list_head *old, struct list_head *newlist)
{
	newlist->next = old->next;
	newlist->next->prev = newlist;
	newlist->prev = old->prev;
	newlist->prev->next = newlist;
}

//˫����Ϊ��
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

//��ȡ"MEMBER��Ա"��"�ṹ��TYPE"�е�λ��ƫ��
#define offsetoff(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
// ����"�ṹ��(type)����"�е�"���Ա����(member)��ָ��(ptr)"����ȡָ�������ṹ�������ָ��
#define container(ptr, type, member) ((type *)((char *)ptr - offsetoff(type, member)))

//����˫������
#define list_for_each(pos, head) \
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
	for(pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_entry(ptr, type, member) \
	container(ptr, type, member)
