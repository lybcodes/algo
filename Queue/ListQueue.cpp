#include<iostream>
#include<memory>
using namespace std;

template<typename T>
struct Node
{
	using ptr_t = std::shared_ptr<Node<T>>; //ptr_t��Node���͵�����ָ��
	T data;
	ptr_t next;

	Node(T data_) :data(data_), next(nullptr) {}  //���캯����ʼ���б�д����
	Node() :next(nullptr) {}
};

template<typename T>
class LinkedQueue
{
public:
	using node_type = Node<T>; //using�÷��൱��typedef
	//һ����typename��class���Ի��������� ����Ҫ��ʾĳ��ʶ�������͵�ʱ��ֻ����typename
	using node_ptr_t = typename node_type::ptr_t; 

private:
	node_ptr_t head_ = nullptr;
	node_ptr_t before_tail_ = nullptr;

public:
	LinkedQueue() = default; //ȱʡ���캯��
	~LinkedQueue() = default;
	
	/*���������ֹ��캯����д��(����c++�Դ��������Ա������=default�������ʹ����Щ��Ա������ =delete�����ֹʹ�������Ա����)*/
	//�������죨�̶�д����
	LinkedQueue(const LinkedQueue &other) = default; 
	//������ֵ���ӣ����ص��Ƕ������ã�Ҳ���Ƿ�����������thisָ�룬��������Ҷ�����a��b��c����������ô���õȺŵ�ʱ�������д a=b=c
	LinkedQueue& operator=(const LinkedQueue& rhs) = default;
	//��ֵ�������ʵ���ƶ����캯��
	LinkedQueue(LinkedQueue&& other) = default;
	//�ƶ���ֵ����
	LinkedQueue& operator=(LinkedQueue&& rhs) = default;

public:
	void enqueue(T item)
	{
		if (nullptr == head_) {
			head_ = std::make_shared<node_type>(item); //��ʼ������ָ��
			before_tail_ = head_;
		}
		else {
			before_tail_->next = std::make_shared<node_type>(item);
			before_tail_ = before_tail_->next;
		}
	}

	T head() const
	{
		if (nullptr != head_) 
		{
			return head_->data;
		}
		else 
		{
			throw "Fetch data from an empty queue!"; //���쳣
		}
	}

	void dequeue()
	{
		if (nullptr != head_)
		{
			head_ = head_->next;
			if (nullptr == head_)
				before_tail_ = nullptr;
		}
		else
			throw "Pop data from an empty queue!";
	}

public:
	template<typename UnaryFunc>
	void traverse(UnaryFunc do_traverse)
	{
		for (node_ptr_t work = head_; nullptr != work; work = work->next)
		{
			do_traverse(work->data);
		}
	}
};



int main()
{
	//lambda���ʽ��д��(Lambda���ڶ��岢���������ĺ�������)
	auto do_traverse = [&](auto item) {std::cout << item << ' '; };

	LinkedQueue<int> linked_queue_1;
	linked_queue_1.enqueue(1);
	linked_queue_1.enqueue(2);
	linked_queue_1.enqueue(3);
	linked_queue_1.traverse(do_traverse);
	std::cout << std::endl;

	LinkedQueue<int> linked_queue_2(linked_queue_1); //copy constructor
	linked_queue_2.traverse(do_traverse);
	std::cout << std::endl;

	//move constructor
	LinkedQueue<int> linked_queue_3(std::move(linked_queue_2));//����Ĺ��캯���β���һ����ֵ���ã���linked_queue_2��һ����ֵ�����Ե�move������ð󶨵���ֵ�ϵ���ֵ����
	linked_queue_3.traverse(do_traverse);
	std::cout << std::endl;
	//����move֮���൱��linked_queue_2�е�����ֱ��ת�Ƶ���linked_queue_3�У����Դ�ӡ2�еĽ���ǿ�
	linked_queue_2.traverse(do_traverse);
	std::cout << std::endl;

	std::cout << linked_queue_3.head() << std::endl;
	linked_queue_3.dequeue();
	std::cout << linked_queue_3.head() << std::endl;
	linked_queue_3.dequeue();
	std::cout << linked_queue_3.head() << std::endl;
	linked_queue_3.dequeue();

	LinkedQueue<int> linked_queue_4;
	linked_queue_4 = linked_queue_1;//copy assignment
	linked_queue_4.traverse(do_traverse);
	std::cout << std::endl;

	LinkedQueue<int> linked_queue_5;
	linked_queue_5 = std::move(linked_queue_4);//move assignment
	linked_queue_5.traverse(do_traverse);
	std::cout << std::endl;
	//����move֮���൱��linked_queue_4�е�����ֱ��ת�Ƶ���linked_queue_5�У����Դ�ӡ4�еĽ���ǿ�
	linked_queue_4.traverse(do_traverse);
	std::cout << std::endl;

	std::cout << linked_queue_5.head() << std::endl;
	linked_queue_5.dequeue();
	std::cout << linked_queue_5.head() << std::endl;
	linked_queue_5.dequeue();
	std::cout << linked_queue_5.head() << std::endl;
	linked_queue_5.dequeue();

	system("pause");
	return 0;
} 