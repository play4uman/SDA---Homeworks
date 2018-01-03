// Zadacha 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>



using namespace std;

int* randNumArray(int n) {
	int* arr = new int[n];
	srand(time(0));
	for (int i = 0; i < n; i++) {
		int temp = rand() % 30;										// Function to create an array of random numebrs between 0 and 29
		arr[i] = temp;												// Starting positons of every new set of stars
	}
	return arr;
}

void positionCursor(int x, int y) {
	COORD cord;
	cord.X = x;
	cord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);  // Function to position the console curson on coords x y
}

void clearRow(int n) {
	if (n < 0) return;
	positionCursor(0, n);											//Function to completely clear row n
	cout << string(80, ' ');
}

void resetConsole() {
	positionCursor(0, 0);
	for (int i = 0; i < 25; i++) {									//Function to clear the whole console
		cout << string(80, ' ');
	}
	positionCursor(0, 0);
}

void printALine(int* src, int n) {
	for (int i = 0; i < n; i++) {
		int curr = src[i];
		for (int i = 0; i < curr; i++) {
			cout << " ";										//Function to print one line with stars
		}
		cout << "*";
	}
	cout << endl;
}

void print(int n) {
	while (true) {
		int* arr = randNumArray(n);
		int real;
		srand(time(0));
		int die = rand() % 19;
		for (int i = -6; i < die; i++) {
			real = i + 6;
			printALine(arr, n);									//the driver fucntion
			clearRow(i);
			positionCursor(0, real);
			Sleep(100);
		}
		resetConsole();
	}
}




int main()
{
	int n = 0;
	cin >> n;
	print(n);
    return 0;
}

