#pragma once

class Product {
	char* SKU;
	char* brand;
	char* model;
	char* category;
	double price;
	int count;
	char* colour;
	char* fabric;
	double length;
public:
	Product();
	Product(char*, char*, char*, char*, double, int, char*, char*, double);
	Product(Product const &);
	Product& operator= (Product const &);
	~Product();

	void setSku(char*);
	void setBrand(char*);
	void setModel(char*);
	void setCategory(char*);
	void setPrice(double);
	void setCount(int);
	void setColour(char*);
	void setFabric(char*);
	void setLength(double);

	char* getSku()const;
	char* getBrand()const;
	char* getModel()const;
	char* getCategory()const;
	double getPrice()const;
	int getCount()const;
	char* getColour()const;
	char* getFabric()const;
	double getLength()const;

};