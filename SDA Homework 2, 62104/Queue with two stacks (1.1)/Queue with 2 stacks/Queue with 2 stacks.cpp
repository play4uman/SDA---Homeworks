// Queue with 2 stacks.cpp : Defines the entry point for the console application.
//
// Do red 154 e moqta implementaciqta na stek. Moje da q ignorirate.

#include "stdafx.h"
#include <assert.h>
#include <iostream>

using namespace std;

template<typename T>
struct node {
	T inf;
	node* link;
};

template <typename T>
class myStack {
private:
	node<T> *start;
	void copyStack(myStack const&);
	void deleteStack();
public:
	myStack();
	myStack(myStack const &);
	myStack& operator= (myStack const &);
	~myStack();
	bool empty() const;
	void push(T const &);
	void pop(T&);
	void top(T&) const;
	void print() const;
	int length() const;
};

template<typename T>
void myStack<T>::copyStack(const myStack<T> & other) {
	if (other.start) {
		node<T>* p = other.start;
		node<T>* s = NULL;
		node<T>* q = NULL;
		assert(start != NULL);
		start->inf = p->inf;
		q = start;
		p = p->link;
		while (p) {
			s = new node<T>;
			assert(s != NULL);
			s->inf = p->inf;
			q->link = s;
			q = s;
			p = p->link;
		}
		q->link = NULL;
	}
	else
		start = NULL;
}

template<typename T>
void myStack<T>::deleteStack() {
	node<T>* p;
	while (start) {
		p = start;
		start = start->link;
		delete p;
	}
}

template<typename T>
bool myStack<T>::empty() const {
	return start == NULL;
}

template<typename T>
void myStack<T>::push(const T& other) {
	node<T>* p = start;
	start = new node<T>;
	assert(start != NULL);
	start->inf = other;
	start->link = p;
}

template<typename T>
void myStack<T>::pop(T& s) {
	node<T>* p = start;
	if (start) {
		s = start->inf;
		start = start->link;
		delete p;
	}
	else {
		cout << "Stack's empty!" << endl;
		exit(1);
	}
}

template<typename T>
void myStack<T>::top(T& other) const {
	if (start) {
		other = start->inf;
	}
	else {
		cout << "Stack's empty!" << endl;
		exit(1);
	}
}

template<typename T>
void myStack<T>::print() const {
	node<T>* p = start;
	while (p) {
		cout << p->inf << endl;
		p = p->link;
	}
}

template<typename T>
int myStack<T>::length() const {
	int counter = 0;
	node<T>* p = start;
	while (p) {
		p = p->link;
		counter++;
	}
	return counter;
}

template<typename T>
myStack<T>::myStack() {
	start = NULL;
}

template<typename T>
myStack<T>::myStack(myStack<T> const & other) {
	copyStack(other);
}

template<typename T>
myStack<T>::~myStack() {
	deleteStack();
}

template<typename T>
myStack<T>& myStack<T>::operator=(myStack<T> const& other) {
	if (this != ohter&) {
		deleteStack();
		copyStack(other);
	}
	return *this;
}


template<class T>
class QueueStacks {
	myStack<T> stack1;
	myStack<T> stack2;

	void deleteQueue();
	void copyQueue();
	void transferOneToTwo();
	void transferTwoToOne();

public:
	QueueStacks();
	QueueStacks(QueueStacks<T> const &);
	QueueStacks<T>& operator= (QueueStacks<T> const &);
	~QueueStacks();


	myStack<T> getStack1();
	myStack<T> getStack2();
	void enqueue(T);
	bool empty() const;
	T dequeue();
	void print();
};

template <typename T>
QueueStacks<T>::QueueStacks() {
}

template <typename T>
QueueStacks<T>::QueueStacks(QueueStacks<T> const & other) {
	stack1 = other.getStack1();
	stack2 = other.getStack2();
}

template <typename T>
QueueStacks<T>& QueueStacks<T>::operator= (QueueStacks<T> const & other) {
	if (this != &other) {
		stack1 = other.getStack1();
		stack2 = other.getStack2();
	}
	return *this;
}

template <typename T>
QueueStacks<T>:: ~QueueStacks() {
	stack1.~myStack();
	stack2.~myStack();
}


template<typename T>
void QueueStacks<T>::transferOneToTwo() {
	while (!stack1.empty()) {
		T x;
		stack1.pop(x);
		stack2.push(x);
	}
}

template<typename T>
void QueueStacks<T>::transferTwoToOne() {
	while (!stack2.empty()) {
		T x;
		stack2.pop(x);
		stack1.push(x);
	}
}

template<typename T>
myStack<T> QueueStacks<T>::getStack1() {
	return stack1;
}

template<typename T>
myStack<T> QueueStacks<T>::getStack2() {
	return stack2;
}

template<typename T>
bool QueueStacks<T>::empty() const {
	return stack1.empty() && stack2.empty();
}


template<typename T>
void QueueStacks<T>::enqueue(T obj) {
	if (stack1.empty()) {
		transferTwoToOne();
		stack1.push(obj);
	}
	else {
		stack1.push(obj);
	}
}

template<typename T>
T QueueStacks<T>::dequeue() {
	T x;
	if (stack1.empty() && stack2.empty()) {
		cerr << "Cannot dequeue from an empty queue!";
		return 0;
	}
	else {
		if (stack2.empty()) {
			transferOneToTwo();
			stack2.pop(x);
		}
		else
			stack2.pop(x);
		return x;
	}
}

template<typename T>
void QueueStacks<T>::print() {
	T x;
	if (stack2.empty()) {
		transferOneToTwo();
	}
	while (!stack2.empty()) {
		stack2.pop(x);
		cout << x << " ";
	}
}

template<typename T>
void concatenateQueues(QueueStacks<T>& source, QueueStacks<T>& other) {
	while (!other.empty()){
		source.enqueue(other.dequeue());
	}
}



int main()
{
	QueueStacks<int> obj1;
	QueueStacks<int> obj2;
	for (int i = 0; i < 5; i++){
		obj1.enqueue(i);
	}

	for (int i = 5; i < 10; i++) {
		obj2.enqueue(i);
	}
	concatenateQueues(obj1, obj2);
	obj1.print();
	
    return 0;
}

