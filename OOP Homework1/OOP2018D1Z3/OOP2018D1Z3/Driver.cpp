#include "stdafx.h"
#include "Store.h"
#include <iostream>

using namespace std;

void createItem(Store& s) {
	Product p;
	char* stringIn = new char[1000];
	double num;
	cout << "Enter the following values:\n";
	cout << "SKU: "; cin.getline(stringIn, 1000); p.setSku(stringIn);
	cout << "Brand: "; cin.getline(stringIn, 1000); p.setBrand(stringIn); 
	cout << "Model: "; cin.getline(stringIn, 1000); p.setModel(stringIn); 
	cout << "Category: "; cin.getline(stringIn, 1000); p.setCategory(stringIn); 
	cout << "Price: "; cin >> num; p.setPrice(num); cin.ignore(); 
	cout << "Count: "; cin >> num; p.setCount(num); cin.ignore(); 
	cout << "Colour: "; cin.getline(stringIn, 1000); p.setColour(stringIn); 
	cout << "Fabric: "; cin.getline(stringIn, 1000); p.setFabric(stringIn); 
	cout << "Length: "; cin >> num; p.setLength(num); cin.ignore(); 
	s.addItem(p);
	delete[] stringIn;
}

void deleteItem(Store& s) {
	char* stringIn = new char[1000];
	cout << "Please enter the SKU of the product you wish to delete: \n";
	cin.getline(stringIn, 1000);
	s.removeItem(stringIn);
}

void changeProduct(Store& s) {
	char* stringIn = new char[1000];
	cout << "Please enter the SKU of the product you wish to change: \n";
	cin.getline(stringIn, 1000);
	s.changeItem(stringIn);
}

void displayProducts(Store& s) {
	s.printAll();
}

int main() {
	Store s;
	start:
	cout << "WELCOME TO \" SOCK SHOP MANAGER 2017\"! Choose an option from the menu below" << endl;
	cout << "A\tAdd new product\nX\tDelete product\nC\tChange product\nD\tDisplay products\nQ\tQuit\n";
	char choice;
	do {
		cin >> choice;
		if (choice != 'A' && choice != 'X' && choice != 'C' && choice != 'D' && choice != 'Q')
			cout << "Please enter a valid letter: ";
	} while (choice != 'A' && choice != 'X' && choice != 'C' && choice != 'D' && choice != 'Q');
	cin.ignore();
	
	char back;
	switch (choice) {
	case'A': createItem(s); 
		cout << "\nPress 'B' to go back to previous menu or any other key to exit.\n";
		cin >> back;
		if (back == 'B') goto start; break;
	case'X': deleteItem(s);
		cout << "\nPress 'B' to go back to previous menu or any other key to exit.\n";
		cin >> back;
		if (back == 'B') goto start; break;
	case'C': changeProduct(s);
		cout << "\nPress 'B' to go back to previous menu or any other key to exit.\n";
		cin >> back;
		if (back == 'B') goto start; break;
	case'D': displayProducts(s);
		cout << "\nPress 'B' to go back to previous menu or any other key to exit.\n";
		cin >> back;
		if (back == 'B') goto start; break;
	case'Q': return 0;
	};
	return 0;
}