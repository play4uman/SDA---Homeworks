// OOP2018D1Z1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T>
struct Node {
	T inf;
	Node* link;
};

template <class T>
class myStack {
	Node<T>* top;
	void copyStack(myStack const &);
	void deleteStack();
public:
	myStack();
	myStack(myStack const&);
	myStack& operator=(myStack const&);
	~myStack();

	void push(T);
	bool isEmpty() const;
	T peek() const;
	T pop();
};

template<class T>
void myStack<T>::copyStack(myStack const & s) {
	if (s.top != NULL) {
		Node<T>* toCopy = s.top;
		Node<T>* newElement = NULL;
		Node<T>* prevElement = NULL;

		newElement = new Node<T>;
		newElement->inf = toCopy->inf;
	    newElement->link = NULL;
		top = newElement;
		prevElement = top;
		toCopy = toCopy->link;
		while (toCopy != NULL) {
			newElement = new Node<T>;
			newElement->inf = toCopy->inf;
			newElement->link = NULL;
			prevElement->link = newElement;
			prevElement = newElement;
			toCopy = toCopy->link;
		}
	}
	else
		top = NULL;
}

template<typename T>
void myStack<T>::deleteStack() {
	Node<T>* toDelete;
	while (top != NULL) {
		toDelete = top;
		top = top->link;
		delete toDelete;
	}
}

template<typename T>
myStack<T>::myStack(myStack const& s) {
	copyStack(s);
}

template<typename T>
myStack<T>::~myStack() {
	deleteStack();
}

template<typename T>
myStack<T>::myStack() {
	top = NULL;
}

template<typename T>
myStack<T>& myStack<T>::operator=(myStack const& s) {
	if (this != &s) {
		deleteStack();
		copyStack(s);
	}
	return *this;
}

template<typename T>
bool myStack<T>::isEmpty() const {
	return top == NULL;
}

template<typename T>
void myStack<T>::push(T toPush) {
	Node<T>* newNode = new Node<T>;
	newNode->inf = toPush;
	newNode->link = top;
	top = newNode;
}

template<typename T>
T myStack<T>::peek() const {
	if (!isEmpty())
		return top->inf;
}

template<typename T>
T myStack<T>::pop() {
	if (!isEmpty()) {
		Node<T>* toDel = top;
		T data = toDel->inf;
		top = top->link;
		delete toDel;
		return data;
	}
	else {
		cout << "Popping from empty stack!";
	}
}

int doTheMath(int left, char op, int right) {
	switch (op) {
	case '+': return left + right;
	case '-': return left - right;
	case '*': return left * right;
	case '/': return left / right;
	case '%': return left % right;
	}
	return 42;
}


int invPolishNot(const char* src, int len) {
	myStack<int> s;
	int leftOperand;
	int rightOperand;

	for (int i = 0; i < len; i++){
		if (src[i] >= '0' && src[i] <= '9') {
			s.push(src[i] - '0');
		}
		else if (src[i] == '+' || src[i] == '-' || src[i] == '*' || src[i] == '/' || src[i] == '%') {
			if (!s.isEmpty()) {
				rightOperand = s.pop();
				if (!s.isEmpty()) {
					leftOperand = s.pop();
					s.push(doTheMath(leftOperand, src[i], rightOperand));
				}
				else {
					cout << "INVALID EXPRESSION!";
				}
			}
			else {
				cout << "INVALID EXPRESSION!";
			}
		}
		else{
			cout << "INVALID EXPRESSION!";
		}
	}
	return s.pop();
}

int main()
{
	char* kor = new char[100000];
	cin >> kor;
	cout << invPolishNot(kor, strlen(kor));
	return 0;
}

