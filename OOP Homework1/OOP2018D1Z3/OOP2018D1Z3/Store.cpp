#include "stdafx.h"
#include <cstring>
#include <iostream>
#include "Store.h"

using namespace std;

Store::Store() {
	items = NULL;
	itemCnt = 0;
}

Store::Store(Store const & other) {
	items = new Product[other.getItemCnt()];
	itemCnt = other.getItemCnt();
	for (int i = 0; i < itemCnt; i++) {
		items[i] = other.items[i];
	}
}

Store& Store::operator=(Store const & other) {
	if (this != &other) {
		delete[] items;
		itemCnt = other.getItemCnt();
		for (int i = 0; i < itemCnt; i++) {
			items[i] = other.items[i];
		}
	}
	return *this;
}

Store::~Store() {
	delete[] items;
}

int Store::getItemCnt()const{
	return itemCnt;
}

void Store::addItem(Product const & toAdd) {
	Product* temp = new Product[itemCnt];
	for (int i = 0; i < itemCnt; i++) {
		temp[i] = items[i];
	}
	delete[] items;
	items = new Product[itemCnt + 1];
	for (int i = 0; i < itemCnt; i++) {
		items[i] = temp[i];
	}
	items[itemCnt] = toAdd;
	itemCnt++;
	delete[] temp;
}

void Store::removeItem(char* _SKU) {
	if (itemCnt == 0) {
		cout << "Error! Inventory is empty.";
		return;
	}

	int indexToDel = -1;
	for (int i = 0; i < itemCnt; i++) {
		if (strcmp(_SKU, items[i].getSku()) == 0) {
			indexToDel = i;
			i = itemCnt;
		}
	}
	if (indexToDel == -1) {
		cout << "No item with SKU " << _SKU << "exists!" << endl;;
		return;
	}

	itemCnt--;
	Product* buffer = new Product[itemCnt];
	for (int i = 0; i < indexToDel; i++) {
		buffer[i] = items[i];
	}
	for (int i = indexToDel + 1; i < itemCnt + 1; i++) {
		buffer[i - 1] = items[i];
	}
	delete[] items;
	items = new Product[itemCnt];
	for (int i = 0; i < itemCnt; i++) {
		items[i] = buffer[i];
	}
	delete[] buffer;
}

void Store::changeItem(char* _SKU) {
	int indexToChange = -1;
	for (int i = 0; i < itemCnt; i++) {
		if (strcmp(_SKU, items[i].getSku()) == 0) {
			indexToChange = i;
			i = itemCnt;
		}
	}
	if (indexToChange == -1) {
		cout << "No item with SKU " << _SKU << "exists!" << endl;;
		return;
	}

	char choice;
	cout << "Please choose an attribute to change (enter the number of the chosen attribute and press enter): " << endl;
	cout << "1: SKU" << endl;
	cout << "2: Brand" << endl;
	cout << "3: Model" << endl;
	cout << "4: Category" << endl;
	cout << "5: Price" << endl;
	cout << "6: Count" << endl;
	cout << "7: Colour" << endl;
	cout << "8: Fabric" << endl;
	cout << "9: Length" << endl;


	do {
		cin >> choice;
			if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' &&
				choice != '7' && choice != '8' && choice != '9') {
				cout << "Please enter a correct value! " << endl;
			}
	} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' &&
		choice != '7' && choice != '8' && choice != '9');
	cin.ignore();

	char* textInput = new char[1000];
	double numInput;

	switch (choice) {
	case '1': cin.getline(textInput, 1000); items[indexToChange].setSku(textInput); break;
	case '2': cin.getline(textInput, 1000); items[indexToChange].setBrand(textInput); break;
	case '3': cin.getline(textInput, 1000); items[indexToChange].setModel(textInput); break;
	case '4': cin.getline(textInput, 1000); items[indexToChange].setCategory(textInput); break;
	case '5': cin >> numInput; items[indexToChange].setPrice(numInput); break;
	case '6': cin >> numInput; items[indexToChange].setCount(numInput); break;
	case '7': cin.getline(textInput, 1000); items[indexToChange].setColour(textInput); break;
	case '8': cin.getline(textInput, 1000); items[indexToChange].setFabric(textInput); break;
	case '9': cin >> numInput; items[indexToChange].setLength(numInput); break;
	}
}

void Store::printAll()const {
	for (int i = 0; i < itemCnt; i++) {
		cout << i + 1 << ": " << items[i].getSku() << "\t" << items[i].getBrand() << "\t" << items[i].getModel() << "\t" <<
			items[i].getCategory() << "\t" << items[i].getPrice() << "\t" << items[i].getCount() << "\t" <<
			items[i].getColour() << "\t" << items[i].getFabric() << "\t" << items[i].getPrice() << endl;
	}
}
