// Apples2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
#include <iostream> 

using namespace std;

struct Point {
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {};			//Pomoshten klas za dyrjene na naredeni dvoiki (tochki)
};

queue<Point> findInitialCoordinates(int** matrix, int rows, int cols) {
	queue<Point> rottenQueue;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++){
			if (matrix[i][j] == 2) {
				rottenQueue.push(Point(i, j));        //Funckiq koqto namira nachalnite koordinati na vsichki izgnili qbylki i gi zapisva v obekti Point, koito 
			}										 // sled tova se zapisvat v opashka.			
		}
	}
	return rottenQueue;
}

bool isFullyRotten(int** matrix, int rows, int cols) {
	int flag = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (matrix[i][j] == 2) {                       // Funckiq koqto proverqva dali na tozi etap vsichki qbylki sa gnili
				flag++;
			}
		}
	}
	return flag == rows*cols;
}


queue<Point> oneTurn(int** matrix, int rows, int cols, queue<Point> oldCoords) {
	queue<Point> newCoords;
	int i = 0, j = 0;
	while (!oldCoords.empty()) {
		i = oldCoords.front().x;
		j = oldCoords.front().y;
		if (i + 1 < rows) {
			if (matrix[i+1][j] == 1) {
				newCoords.push(Point(i + 1, j));
			}
		}
		if (i - 1 >= 0) {
			if (matrix[i - 1][j] == 1) {
				newCoords.push(Point(i - 1, j));  //Funkciq, koqto po podadena matrica i koordinati na loshi qbylki vrysta nova opashka sys vsichki
			}									  // gnili qbylki v rezultat na gnieneto na zapisanite v oldCoords.
		}
		if (j + 1 < cols) {
			if (matrix[i][j + 1] == 1) {
				newCoords.push(Point(i, j + 1)); 
			}
		}
		if (j - 1 >= 0) {
			if (matrix[i][j - 1] == 1) {
				newCoords.push(Point(i, j - 1));
			}
		}
		oldCoords.pop();
	}
	return newCoords;
}

int** updateMatrix(int** matrix, int rows, int cols, queue<Point> coords) {
	int i = 0;
	int j = 0;

	while (!coords.empty()) {
		i = coords.front().x;					//Funckiq koqto otbelqzva vsichki qbylki, okolo podadenite v coords loshi qbylki, kato loshi
		j = coords.front().y;
		matrix[i][j] = 2;
		coords.pop();
	}
	return matrix;
}

int countTurns(int** matrix, int rows, int cols) {
	int turnCounter = 0;
	queue<Point> current = findInitialCoordinates(matrix, rows, cols); 
	while (!isFullyRotten(matrix, rows, cols)) {		// While se izpylnqva dokato vsichki qbylki ne stanat gnili.
		current = oneTurn(matrix, rows, cols, current); // current dyrji mestopolojenieto na vsichki novi gnili qbylki sled 1 hod
		matrix = updateMatrix(matrix, rows, cols, current); // matricata se update-va sprqmo tova mestopolojenie
		turnCounter++;									//Counter koito broi broq na hodovete. Vsqko izpylnenie na while-a dobavq edin hod.
	}
	return turnCounter;
}

bool forOneTurn(int** matrix, int rows, int cols) {
	queue<Point> current = findInitialCoordinates(matrix, rows, cols);
	current = oneTurn(matrix, rows, cols, current);
	matrix = updateMatrix(matrix, rows, cols, current);   //Funckiq koqto proverqva dali vsichki qbylki shte izgniqt za 1 hod
	return isFullyRotten(matrix, rows, cols);
}


int main()
{
	int n = 0, m = 0;                                   //Vyvedete izmereniqta na matricata
	cin >> m >> n;
	int** matrix = new int*[m];             
	for (int i = 0; i < m; i++) {                       // Vyvedete matricata
		matrix[i] = new int[m];
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			cin >> matrix[i][j];
		}
	}
	cout << countTurns(matrix, m, n);
	

	for (int i = 0; i < m; i++){
		delete[] matrix[i];                       //Osvobojdavame pametta
	}
    return 0;
}

