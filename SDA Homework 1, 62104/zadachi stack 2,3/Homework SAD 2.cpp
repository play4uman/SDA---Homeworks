// Homework SAD 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h> 
#include <limits.h>

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
int myStack<T>::length() const{
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


void maximumElement() {
	cout << "Welcome to Maximum Element!" << endl;
	myStack<int> stack1;
	int n = 0;
	int query = 0;
	int value = 0;
	int max = INT_MIN;
	int current = 0;
	do {
		cout << "Please enter a valid number of queries: ";
		cin >> n;
	} while (n <= 0);
	cout << "Please enter a valid query: \n 1 - Push element in stack. \n 2 - Pop element from stack \n 3 - Show stack's current maximal element \n";
	while (n > 0) {
		do {
			cout << "Please enter a valid query: ";
			cin >> query;
			cout << " ";
		} while (query < 1 || query > 3);

		switch (query) {
		case 1: cin >> value;
			stack1.push(value);
			break;
		case 2: stack1.pop(value);
			break;
		case 3:
			while (!stack1.empty()) {
				stack1.pop(current);
				if (current > max) {
					max = current;
				}
			}
			cout << "current max = " << max << endl;
			break;
		}
		n--;
	}
	int buff;
	cout << "Press any key to exit Maximal Element" << endl;
	cin >> buff;
}

void gameOfStacks() {
	cout << "Welcome to Game of Stacks!" << endl;
	myStack<int> stack1, stack2;
	int g = 0;
	int m = 0;
	int n = 0;
	int x = 0;
	int counter = 0;
	int score = 0;
	int leftTop = 0, rightTop = 0;
	cin >> g;
	cin >> m >> n >> x;
	int* arrM = new int[m];
	int* arrN = new int[n];
	for (int i = 0; i < m; i++){
		cin >> arrM[i];
	}
	for (int i = 0; i < n; i++){
		cin >> arrN[i];
	}

	for (int i = m - 1; i >= 0; i--){
		stack1.push(arrM[i]);
	}

	for (int i = n - 1; i >= 0; i--){
		stack2.push(arrN[i]);
	}

	for (int i = 0; i < g; i++){
		while (counter <= x) {
			if (!stack1.empty()) {
				stack1.pop(leftTop);
			}
			if (!stack2.empty()) {
				stack2.pop(rightTop);
			}
			if (leftTop <= rightTop) {
				counter += leftTop;
				stack2.push(rightTop);
			}
			else {
				counter += rightTop;
				stack1.push(leftTop);
			}

			if (counter <= x) {
				score++;
			}
		}
		cout << "Score of game " << i + 1<< " = " << score << endl;
	}
	int buff;
	cout << "Press any key to exit Game of Stacks" << endl;
	cin >> buff;
	delete[] arrM;
	delete[] arrN;
}



int main()
{
	maximumElement();
	gameOfStacks();
    return 0;
}

