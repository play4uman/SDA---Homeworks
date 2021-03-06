// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//Priemame che imame pravilno implementiran List, koito e izgraden ot obekti tip Node<T>
//Alternativno reshenie na zadachata e izpolzvaneto na std::list i izpolzvaneto na fukciite list::sort() i list::unique()

#include "stdafx.h"
#include <iostream>

using namespace std;

template<class T>
class Node {
public:
	T inf;
	Node<T>* link;
};


template<typename T>
Node<T>* removeDuplicates(Node<T>* head) {
	Node<T>* start = head;
	if (head) {
		while (head) {
			T current = head->inf;
			Node<T>* q = head->link;
			if (q->inf == current) {
				head = q->link;
				delete q;
			}
			else {
				head = head->link;
			}
		}
	}
	else {
		cerr << "Empty Stack!";
	}
	return start;
}


int main()
{
    return 0;
}

