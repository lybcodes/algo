//���������궼��Linux�ں����õ���,��������һЩGCC��C��չ���﷨�޷���VC++�б���ͨ��
#define offsetoff(TYPE,MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/*���ݵ�ǰ�ṹ��Ԫ�صĵ�ַ����ȡ���ṹ���׵�ַ*/
//������л���
//1. ( (TYPE *)0 ) ����ת��ΪTYPE����ָ��; 
//2. ((TYPE *)0)->MEMBER ���ʽṹ�е����ݳ�Ա; 
//3. &( ( (TYPE *)0 )->MEMBER )ȡ�����ݳ�Ա�ĵ�ַ; 
//4.(size_t)(&(((TYPE*)0)->MEMBER))���ת�����͡�����֮�����ڽ�0ת ����(TYPE*)���ṹ���ڴ�ռ��׵�ַ0��Ϊ��ʼ��ַ�����Ա��ַ��ȻΪƫ�Ƶ�ַ��
//TYPE��ĳstruct������ 0��һ������TYPE����struct,MEMBER�Ǹ�struct�е�һ����Ա. ���ڸ�struct�Ļ���ַΪ0, MEMBER�ĵ�ַ���Ǹó�Ա�����structͷ��ַ��ƫ����

//#define container(ptr,type,member) ({\
//  const typeof(((type *)0)->member) *__mptr = (ptr);\
//  (type *) ((char*)__mptr - offsetoff(type,member));\
//})
#define container(ptr, type, member) (type*)((char*)(ptr) - offsetoff(type, member))
//���ڻ��ĳ�ṹ��ĳ��Ա����ڵ�ַ.
//const typeof( ((type *)0->member ) *__mptr = (ptr);��˼������һ����memberͬһ�����͵�ָ�볣�� *__mptr,����ptrֵ������.
//(type *)( (char *)__mptr - offsetof(type,member) );��˼��__mptr�ĵ�ַ��ȥmember�ڸ�struct�е�ƫ�����õ��ĵ�ַ, ��ת����type��ָ��. ��ָ����ǽṹ�����ڵ�ַ��.


typedef struct _hashtab_node
{
	void *key; //ÿ���ڵ㶼������ԭʼ���±�ֵkey
	void *data;
	struct _hashtab_node *next;
}hashtab_node;

typedef struct _hashtab
{
	hashtab_node **htables; //��ϣͰ �ȼ���hashtab_node *[] htables
	int size;               //��ϣͰ���������
	int nel;                //Ͱ��Ԫ�صĸ���
	int(*hash_value)(struct _hashtab *h, const void *key); //��ϣ����
	int(*keycmp)(struct _hashtab *h, const void *key1, const void *key2);//��ϣkey�ȽϺ���������ϣ��ֵһ��ʱʹ��
	void(*hash_node_free)(hashtab_node *node);

}hashtab;

#define HASHTAB_MAX_NODES  (0xffffffff) //2��32��

//���庯��ָ��
typedef int(*hash_key_func)(struct _hashtab *h, const void *key); /*��ϣ����*/
typedef int(*keycmp_func)(struct _hashtab *h, const void *key1, const void *key2);/*��ϣkey�ȽϺ���������ϣ��ֵһ��ʱʹ��*/
typedef void(*hash_node_free_func)(hashtab_node *node);



hashtab * hashtab_create(int size, hash_key_func hash_value,
	keycmp_func keycmp, hash_node_free_func hash_node_free);
void hashtab_destory(hashtab *h);
int hashtab_insert(hashtab * h, void *key, void *data);
hashtab_node *hashtab_delete(hashtab *h, void *key);
void *hashtab_search(hashtab*h, void *key);

