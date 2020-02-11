#include <iostream>



template <typename T>
class CircularQueue
{
private:
	T*     items_ = nullptr;
	size_t capacity_ = 0;
	size_t head_ = 0;
	size_t tail_ = 0;

public:
	CircularQueue() = delete; //不使用默认构造函数
	//自己写的构造函数
	CircularQueue(const size_t capacity) :capacity_(capacity) 
	{
		items_ = new T[capacity_];
	}  //构造函数初始化列表写法

	~CircularQueue()
	{
		if (nullptr != items_)
		{
			delete[] items_;
			items_ = nullptr;
		}
	}

	//拷贝构造函数
	CircularQueue(const CircularQueue& other) : capacity_(other.capacity_) 
	{
		items_ = new T[capacity_];
		for (size_t i = other.head_; i != other.tail_; ++i) 
		{
			enqueue(other.items_[i]);
		}
	}

	//拷贝赋值算子
	CircularQueue& operator=(const CircularQueue& rhs) 
	{
		delete[] items_;
		head_ = 0;
		tail_ = 0;
		capacity_ = rhs.capacity_;
		items_ = new T[capacity_];
		for (size_t i = rhs.head_; i != rhs.tail_; ++i) 
		{
			enqueue(rhs.items_[i]);
		}
		return *this;
	}

	//移动构造函数
	CircularQueue(CircularQueue&& other) :items_(other.items_),
		capacity_(other.capacity_),
		head_(other.head_),
		tail_(other.tail_) 
	{
		other.items_ = nullptr;
		other.capacity_ = 0;
		other.head_ = 0;
		other.tail_ = 0;
	}

	//移动赋值算子
	CircularQueue& operator=(CircularQueue&& rhs)
	{
		delete[] items_;
		items_ = rhs.items_;
		capacity_ = rhs.capacity_;
		head_ = rhs.head_;
		tail_ = rhs.tail_;
		rhs.items_ = nullptr;
		rhs.capacity_ = 0;
		rhs.head_ = 0;
		rhs.tail_ = 0;
		return *this;
	}

public:
	void enqueue(T item)
	{
		if ((tail_ + 1) % capacity_ == head_) //满队
		{
			throw "push data into a full queue!";
		}
		items_[tail_] = item;
		tail_ = (tail_ + 1) % capacity_;
	}

	T head()const
	{
		if (head_ != tail_) //head_和tail_相等即为队空
			return items_[head_];
		else
			throw "Fetch data from an empty queue!";
	}

	void dequeue()
	{
		if (head_ != tail_)
			head_ = (head_ + 1) % capacity_;
		else
			throw "Pop data from an empty queue!";
	}

public:
	template<typename UnaryFunc>
	void traverse(UnaryFunc do_traverse)
	{
		if (0 == capacity_) return;
		for (size_t i = head_; i%capacity_ != tail_; ++i)
		{
			do_traverse(items_[i%capacity_]);
		}
	}
};


int main()
{
	auto do_traverse = [&](auto item) {std::cout << item << ' '; };

	CircularQueue<int> circular_queue_1(4);
	circular_queue_1.enqueue(1);
	circular_queue_1.enqueue(2);
	circular_queue_1.enqueue(3);
	//circular_queue_1.enqueue(4); //head和tail从0开始，所以
	circular_queue_1.traverse(do_traverse);
	std::cout << std::endl;

	CircularQueue<int> circular_queue_2(circular_queue_1);// copy constructor
	circular_queue_2.traverse(do_traverse);
	std::cout << std::endl;

	CircularQueue<int> circular_queue_3(std::move(circular_queue_2));// move constructor
	circular_queue_3.traverse(do_traverse);
	std::cout << std::endl;
	circular_queue_2.traverse(do_traverse);
	std::cout << std::endl;

	std::cout << circular_queue_3.head() << std::endl;
	circular_queue_3.dequeue();
	std::cout << circular_queue_3.head() << std::endl;
	circular_queue_3.dequeue();
	std::cout << circular_queue_3.head() << std::endl;
	circular_queue_3.dequeue();

	CircularQueue<int> circular_queue_4(1);
	circular_queue_4 = circular_queue_1; // copy assignment
	circular_queue_4.traverse(do_traverse);
	std::cout << std::endl;

	CircularQueue<int> circular_queue_5(100);
	circular_queue_5 = std::move(circular_queue_4);  // move assignment
	circular_queue_5.traverse(do_traverse);
	std::cout << std::endl;
	circular_queue_4.traverse(do_traverse);
	std::cout << std::endl;

	std::cout << circular_queue_5.head() << std::endl;
	circular_queue_5.dequeue();
	std::cout << circular_queue_5.head() << std::endl;
	circular_queue_5.dequeue();
	std::cout << circular_queue_5.head() << std::endl;
	circular_queue_5.dequeue();

	system("pause");
	return 0;
}