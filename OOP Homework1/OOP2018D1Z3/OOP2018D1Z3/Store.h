#pragma once

#include "Product.h"

class Store {
	Product* items;
	int itemCnt;

public:
	Store();
	Store(Store const &);
	Store& operator=(Store const &);
	~Store();

	int getItemCnt()const;
	void addItem(Product const &);
	void removeItem(char* _SKU);
	void changeItem(char* _SKU);
	void printAll()const;
};