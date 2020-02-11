//下面两个宏都是Linux内核中用到的,但是其中一些GCC对C拓展的语法无法在VC++中编译通过
#define offsetoff(TYPE,MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/*根据当前结构体元素的地址，获取到结构体首地址*/
//宏的运行机理：
//1. ( (TYPE *)0 ) 将零转型为TYPE类型指针; 
//2. ((TYPE *)0)->MEMBER 访问结构中的数据成员; 
//3. &( ( (TYPE *)0 )->MEMBER )取出数据成员的地址; 
//4.(size_t)(&(((TYPE*)0)->MEMBER))结果转换类型。巧妙之处在于将0转 换成(TYPE*)，结构以内存空间首地址0作为起始地址，则成员地址自然为偏移地址；
//TYPE是某struct的类型 0是一个假想TYPE类型struct,MEMBER是该struct中的一个成员. 由于该struct的基地址为0, MEMBER的地址就是该成员相对与struct头地址的偏移量

//#define container(ptr,type,member) ({\
//  const typeof(((type *)0)->member) *__mptr = (ptr);\
//  (type *) ((char*)__mptr - offsetoff(type,member));\
//})
#define container(ptr, type, member) (type*)((char*)(ptr) - offsetoff(type, member))
//用于获得某结构中某成员的入口地址.
//const typeof( ((type *)0->member ) *__mptr = (ptr);意思是声明一个与member同一个类型的指针常量 *__mptr,并将ptr值赋给它.
//(type *)( (char *)__mptr - offsetof(type,member) );意思是__mptr的地址减去member在该struct中的偏移量得到的地址, 再转换成type型指针. 该指针就是结构体的入口地址了.


typedef struct _hashtab_node
{
	void *key; //每个节点都保留其原始的下标值key
	void *data;
	struct _hashtab_node *next;
}hashtab_node;

typedef struct _hashtab
{
	hashtab_node **htables; //哈希桶 等价于hashtab_node *[] htables
	int size;               //哈希桶的最大数量
	int nel;                //桶中元素的个数
	int(*hash_value)(struct _hashtab *h, const void *key); //哈希函数
	int(*keycmp)(struct _hashtab *h, const void *key1, const void *key2);//哈希key比较函数，当哈希数值一致时使用
	void(*hash_node_free)(hashtab_node *node);

}hashtab;

#define HASHTAB_MAX_NODES  (0xffffffff) //2的32次

//定义函数指针
typedef int(*hash_key_func)(struct _hashtab *h, const void *key); /*哈希函数*/
typedef int(*keycmp_func)(struct _hashtab *h, const void *key1, const void *key2);/*哈希key比较函数，当哈希数值一致时使用*/
typedef void(*hash_node_free_func)(hashtab_node *node);



hashtab * hashtab_create(int size, hash_key_func hash_value,
	keycmp_func keycmp, hash_node_free_func hash_node_free);
void hashtab_destory(hashtab *h);
int hashtab_insert(hashtab * h, void *key, void *data);
hashtab_node *hashtab_delete(hashtab *h, void *key);
void *hashtab_search(hashtab*h, void *key);

