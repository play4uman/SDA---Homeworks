// Zadacha 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

int* randNumArray(int n) {
	int* arr = new int[n];
	srand(time(0));
	for (int i = 0; i < n; i++) {
		int temp = rand() % 30;
		arr[i] = temp;
	}
	return arr;
}

void printALine(int* src, int n) {
	for (int i = 0; i < n; i++) {
		int curr = src[i];
		for (int i = 0; i < curr; i++) {
			cout << " ";
		}
		cout << "*";
	}
	cout << endl;
}

void print(int n) {
	while (true) {
		int* arr = randNumArray(n);
		for (int i = -6; i < 25; i++) {
			printALine(arr, n);
		}
	}
}


int main()
{
	int n = 0;
	cin >> n;
	print(n);
    return 0;
}

