// Cycle Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

struct Node {
	int inf;
	Node* link;
};

bool cycleDetect(Node* head) {
	std::vector<Node*> visited;									//vector, koito dyrji adresite na vsichki poseteni kutii
	Node* p = head;
	visited.push_back(p);										// v nachaloto vectora dyrji samo head-a na spisyka
	while (p->link) {											//dokato ne stignem NULL (ako ima takyv)
		visited.push_back(p->link);								//vyv vectora pushvame nai - nakraq adresa na sledvashtata kutiq
		for (int i = 0; i < visited.size() - 1; i++){			//minavame prez vsichki pushnati do tozi moment elementi bez posledniq
			if (vector[i] == vector[visited.size() - 1]) {		// ako nqkyde ima syvpadenie, oznachava che veche vednij sme minali prez tazi kutiq
				return true;									// ima cikyl -> vyrni true.
			}
		}
		p = p->link;
	}
	return false;												//ako sme stignali do NULL, oznachava che e nqmalo syvpadenie -> nqma cikli. vyrni false
}

int main()
{
    return 0;
}

