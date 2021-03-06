// Reverse List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template<class T>
struct Node {
	T inf;
	Node<T>* prev;
	Node<T>* next;
};

template<typename T>
Node<T>* end(Node<T>* head) {
	Node<T>* p = head;
	while (p) {
		if (p->next == NULL) {                          //Pomoshtna funckiq za namirane na adresa na posledniq element po zadadeno nachalo na spisyk.
			return p;								   //Vryshta NULL ako mu e podaden prazen spisyk
		}
		p = p->next;
	}
}

template<typename T>
Node<T>* reverse(Node<T>* head) {
	Node<T>* right;
	Node<T>* mid;
	Node<T>* left;
	mid = end(head);                               //pointera mid sochi kym poslednata kutiika v originalniq spisyk
	if (mid) {
		right = mid->next;							   // right sochi kym sledvashtata kutiika (vdqsno)
		left = mid->prev;							   // left sochi kym predhodnata (vlqvo)
		while (left->prev) {
			mid->prev = right;                        // zapochvaiki ot zad, nasochvame vsqko edno ot poletata na mid kutiikata da obyrne socheneto si
			mid->next = left;
			right = mid;
			mid = left;                               //premestvame left, mid, right enda poziciq nalqvo
			left = left->prev;
		}
	}
	else {
		cerr << "Cannot reverse empty list";
	}
	return end(head);
}

int main()
{
    return 0;
}

