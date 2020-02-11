#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
using namespace std;

enum {DEFAULT_SIZE = 10};

template<typename T>
class Heap
{
public:
	Heap() = default;
	virtual ~Heap() = default;
public:
	virtual void show_heap()const = 0;
	virtual bool insert_heap(const T&) = 0;
	virtual bool remove_heap(T&) = 0;
};

#endif