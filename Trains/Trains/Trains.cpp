// Trains.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
using namespace std;



struct Person {
	char gender;
	int age;
	Person(char c, int a) : gender(c), age(a) {};
	Person() : gender('x'), age(0) {};
	Person& operator= (Person const & other) {
		gender = other.gender;
		age = other.age;
	}
};

class Train {
	vector<stack<Person>> trainStack;
	vector<queue<Person>> trainQueue;
public:

	void addStack(stack<Person> toAdd) {
		trainStack.push_back(toAdd);
	}

	void addQueue(queue<Person> toAdd) {
		trainQueue.push_back(toAdd);
	}

	void addPersonToStackX(Person p, int x) {
		if (x < trainStack.size()) {
			trainStack[x].push(p);
		}
	}

	void addPersonToQueueX(Person p, int x) {
		if (x < trainQueue.size()) {
			trainQueue[x].push(p);
		}
	}


	list<Person> getAllPeople() {
		list<Person> buff;
		for (int i = 0; i < trainStack.size(); i++) {
			while (!trainStack[i].empty()) {
				buff.push_back(trainStack[i].top);
				trainStack[i].pop();
			}													//Funckiq koqto sybira vsichki hora ot edin vlak i gi postavq vyv list.
		}

		for (int i = 0; i < trainQueue.size(); i++) {
			while (!trainQueue[i].empty()) {
				buff.push_back(trainQueue[i].front());
				trainQueue[i].pop();
			}
		}
		return buff;
	}


	void allocatePeopleEqually() {

		list<Person> buff = getAllPeople();					//Sybirame vsichki hora ot tekushtiq vlak
		int perWagon = buff.size() / trainStack.size() + trainQueue.size();	 //Namirame chelochisleno kolko hora trqbva da ima vyv vagon. Ako obshto sa 47 i imame 8 vagona, poluchavame 5.
		int remainder = buff.size() % trainStack.size() + trainQueue.size(); // Po modul, shte poluchim 7.

		for (int i = 0; i < trainStack.size(); i++) {
			for (int p = 0; p < perWagon; p++){
				if (!buff.empty()) {
					trainStack[i].push(buff.back());                 //Razpredelqme chelochisleno horata ravnomerno (pyrvo vyv Queue vagonite). 
					buff.pop_back();	
				}
			}
		}

		for (int i = 0; i < trainQueue.size(); i++) {
			for (int p = 0; p < perWagon; p++){
				if (!buff.empty()) {
					trainQueue[i].push(buff.back());				//posle vyv stack vagonite
					buff.pop_back();
				}
			}
		}

		while (remainder != 0) {
			for (int i = 0; i < trainQueue.size(); i++) {
				if (!buff.empty() && remainder) {
					trainQueue[i].push(buff.back());            //Razpredelqme po modul ravnomerno vyv queue vagonite
					buff.pop_back();
					remainder--;
				}
			}

			for (int i = 0; i < trainStack.size(); i++) {
				if (!buff.empty() && remainder) {
					trainQueue[i].push(buff.back());		// vyv stack vagonite
					buff.pop_back();
					remainder--;
				}
			}
		}

	}

	void reallocatePeopleToAnotherTrain(Train& other) {
		list<Person> buff = getAllPeople();									// Vzemame vsichki hora ot tekushtiq vlak
		stack<Person> women;
		for (list<Person>::iterator i = buff.begin(); i != buff.end(); i++) {		//Ot tqh izkarvame vsichki Personi ot tip F i gi pushvame vyv steka women.
			if (i->gender == 'F'){
				women.push(*i);
				buff.erase(i);
			}
		}

		int perWagon = buff.size() + women.size() / other.trainQueue.size() + other.trainStack.size();
		int remainder = buff.size() + women.size() % other.trainQueue.size() + other.trainStack.size();

		while (true) {
			for (int i = 0; i < other.trainQueue.size(); i++) {
				for (int p = 0; p < perWagon; p++) {
					if (!buff.empty()) {
						other.trainQueue[i].push(buff.back());			//Pushvame posledovatelno horata ot razzlichni polove vyv Queue vagoni
						buff.pop_back();								// Ako ostanat poveche ot ediniq pol, shte bydat postaveni v poslednite vagoni
					}
					if (!women.empty()) {
						other.trainQueue[i].push(women.top());
						women.pop();
					}
				}
			}

			for (int i = 0; i < other.trainStack.size(); i++) {
				for (int p = 0; p < perWagon; p++) {
					if (!buff.empty()) {
						other.trainStack[i].push(buff.back());       //Pushvame posledovatelno horata ot razzlichni polove vyv Stack vagoni
						buff.pop_back();							//// Ako ostanat poveche ot ediniq pol, shte bydat postaveni v poslednite vagoni
					}
					if (!women.empty()) {
						other.trainStack[i].push(women.top());
						women.pop();
					}
				}
			}
			break;
		}
		
		while (remainder != 0) {
			for (int i = 0; i < trainQueue.size(); i++) {
				if (!buff.empty() && remainder) {
					other.trainQueue[i].push(buff.back());
					buff.pop_back();
					remainder--;
				}
				if (!women.empty() && remainder) {
					other.trainQueue[i].push(women.top());
					women.pop();
					remainder--;
				}
			}

			for (int i = 0; i < trainStack.size(); i++) {					//razpredelqme ostatyka
				if (!buff.empty() && remainder) {
					other.trainStack[i].push(buff.back());
					buff.pop_back();
					remainder--;
				}
				if (!women.empty() && remainder) {
					other.trainStack[i].push(women.top());
					women.pop();
					remainder--;
				}
			}
		}

	}

	void sortWagons() {
		double age = 0;
		int counter = 0;
		vector<double> avgStack;						      //Vektori koito da pazqt srednite stoinosti na vyzrastite na vseki vagon
		vector<double> avgQueue;
		for (int i = 0; i < trainQueue.size(); i++) {
			queue<Person> buffQueue = trainQueue[i];
			for (int p = 0; p < buffQueue.size(); p++) {
				age += buffQueue.front().age;
				buffQueue.pop();
				counter++;
			}
			age /= counter;
			avgQueue.push_back(age);							//zapisvame stoinostite v syshtiq red v koito sa vagonite. 1:1 syotvestvie
		}														// mejdu index na vagon i index na srednata mu vyzrast

		age = 0;
		counter = 0;

		for (int i = 0; i < trainStack.size(); i++) {
			stack<Person> buffStack = trainStack[i];
			for (int i = 0; i < buffStack.size(); i++) {
				age += buffStack.top().age;
				buffStack.pop();
				counter++;
			}
			age /= counter;
			avgStack.push_back(age);                         //syshtoto kato gornoto
		}
		int i, j = 0;
		for (i = 0; i < avgQueue.size() - 1; i++) {
			for (j = 0; j < avgQueue.size() - i - 1; i++){
				if (avgQueue[j] > avgQueue[j + 1]) {
					double temp = avgQueue[j];
					avgQueue[j] = avgQueue[j + 1];		//Bubble sort za vektora na Quetata (i sredinte stoinosti na vagonite ot tip Queue)
					avgQueue[j + 1] = temp;

					queue<Person> tempO = trainQueue[j];
					trainQueue[j] = trainQueue[j + 1];
					trainQueue[j + 1] = tempO;
				}
			}
		}


		for (i = 0; i < avgStack.size() - 1; i++) {
			for (j = 0; j < avgStack.size() - i - 1; i++) {
				if (avgStack[j] > avgStack[j + 1]) {
					double temp = avgStack[j];
					avgStack[j] = avgStack[j + 1];
					avgStack[j + 1] = temp;					//Bubble sort za vektora na Stekovete(i sredinte stoinosti na vagonite ot tip Stack)

					stack<Person> tempO = trainStack[j];
					trainStack[j] = trainStack[j + 1];
					trainStack[j + 1] = tempO;
				}
			}
		}

														//Dvete kompozicii sa sortirane po narastvane na srednata vyzrast na vski edin vagon.
	}
};


int main()
{
    return 0;
}

