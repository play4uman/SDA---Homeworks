// MergeTwoLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template<typename T>
struct Node {
	T inf;
	Node<T>* link;
};

template<typename T>
Node<T>* mergeLists(Node<T>* headA, Node<T>* headB) {
	Node<T>* iterA = headA;
	Node<T>* iterB = headB;
	int counter = 1;
	Node<T>* previous;									// previous shte dyrji poslednata kutiika na noviq spisyk. (predi syzdavaneto na nova takava)
	Node<T>* next;										// next shte e pointer kym novosyzdadena kutiika
	Node<T>* newHead = NULL;
	while (iterA || iterB) {                           //Ako vse oshte ima neobhodeni elementi v koito i da e ot dvata lista izpylni:
		next = new Node<T>;							   // 1. Syzdai nova "kutiika" v koqto shte se dyrji stoinostta na sortiran element
		if (counter == 1) {
			newHead = next;                       // Ako tova e pyrvata syzdadena kutiika na noviq spisyk zapazi neinata stoinost v promenlivata newHead
			previous = next;					  //Edinstveniq sluchai v koito previous i next sochat edna i syshta kuttika - nachaloto na noviq list.
		}
		counter++;
		previous->link = next;                   //2. Nasochi link dannata na previous da sochi kym novosyzdadenata kutiika
		previous = next;						//3. Previous veche sochi kym novozydadenata kutiika
		if (iterA && iterB) {
			if (iterA->inf <= iterB->inf) {     //4.1 Ako i v dvata spisyka ima elementi, sravni tekushtiq im element. Chiito element e po malyk 
				next->inf = iterA->inf;         // go sloji kato chlen danna inf v novosyzdadenata kutiika. Proverkata e nujna za da se podsigurni validnostta
				iterA = iterA->link;			// na if-a na red 30.
			}
			else {
				next->inf = iterB->inf;
				iterB = iterB->link;
			}
		}
		else if (iterA) {
			next->inf = iterA->inf;             //4.2 ako ima samo v spisyk 1, kopirtai samo ot spisyk 1
			iterA = iterA->link;
		}
		else if(iterB){
			next->inf = iterB->inf;           //4.3 ako ima samo v spisyk 2, kopirai samo ot spisyk 2
			iterB = iterB->link;
		}
	}
	return newHead;
}

int main()
{
    return 0;
}

