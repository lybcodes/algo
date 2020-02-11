#include<iostream>
#include<memory>
using namespace std;

template<typename T>
struct Node
{
	using ptr_t = std::shared_ptr<Node<T>>; //ptr_t是Node类型的智能指针
	T data;
	ptr_t next;

	Node(T data_) :data(data_), next(nullptr) {}  //构造函数初始化列表（写法）
	Node() :next(nullptr) {}
};

template<typename T>
class LinkedQueue
{
public:
	using node_type = Node<T>; //using用法相当于typedef
	//一般下typename和class可以互换，但是 当需要表示某标识符是类型的时候只能用typename
	using node_ptr_t = typename node_type::ptr_t; 

private:
	node_ptr_t head_ = nullptr;
	node_ptr_t before_tail_ = nullptr;

public:
	LinkedQueue() = default; //缺省构造函数
	~LinkedQueue() = default;
	
	/*下面是四种构造函数的写法(都是c++自带的特殊成员函数，=default代表可以使用这些成员函数， =delete代表禁止使用这个成员函数)*/
	//拷贝构造（固定写法）
	LinkedQueue(const LinkedQueue &other) = default; 
	//拷贝赋值算子，返回的是对象引用，也就是返回这个对象的this指针，所以如果我定义了a，b，c三个对象，那么我用等号的时候可以连写 a=b=c
	LinkedQueue& operator=(const LinkedQueue& rhs) = default;
	//右值引用配合实现移动构造函数
	LinkedQueue(LinkedQueue&& other) = default;
	//移动赋值算子
	LinkedQueue& operator=(LinkedQueue&& rhs) = default;

public:
	void enqueue(T item)
	{
		if (nullptr == head_) {
			head_ = std::make_shared<node_type>(item); //初始化智能指针
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
			throw "Fetch data from an empty queue!"; //抛异常
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
	//lambda表达式的写法(Lambda用于定义并创建匿名的函数对象)
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
	LinkedQueue<int> linked_queue_3(std::move(linked_queue_2));//这里的构造函数形参是一个右值引用，而linked_queue_2是一个左值，所以调move函数获得绑定到左值上的右值引用
	linked_queue_3.traverse(do_traverse);
	std::cout << std::endl;
	//调了move之后，相当于linked_queue_2中的数据直接转移到了linked_queue_3中，所以打印2中的结果是空
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
	//调了move之后，相当于linked_queue_4中的数据直接转移到了linked_queue_5中，所以打印4中的结果是空
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