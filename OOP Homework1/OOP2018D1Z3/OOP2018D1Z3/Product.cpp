// OOP2018D1Z3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <iostream>
#include "Product.h"

using namespace std;

Product::Product() {
	SKU = NULL;
	brand = NULL;
	model = NULL;
	category = NULL;
    price = 0;
	count = 0;
	colour = NULL;
	fabric = NULL;
	length = 0;
}

Product::Product(char* _SKU, char* _brand, char* _model, char* _category, double _price, int _count,
	char* _colour, char* _fabric, double _length) {
	SKU = new char[strlen(_SKU) + 1]; strcpy(SKU, _SKU);
	brand = new char[strlen(_brand) + 1]; strcpy(brand, _brand);
	model = new char[strlen(_model) + 1]; strcpy(model, _model);
	category = new char[strlen(_category) + 1]; strcpy(category, _category);
	price = _price;
	count = _count;
	colour = new char[strlen(_colour) + 1]; strcpy(colour, _colour);
	fabric = new char[strlen(_fabric) + 1]; strcpy(fabric, _fabric);
	length = _length;
}

Product::Product(Product const & other) {
		SKU = new char[strlen(other.getSku()) + 1]; strcpy(SKU, other.getSku());
		brand = new char[strlen(other.getBrand()) + 1]; strcpy(brand, other.getBrand());
		model = new char[strlen(other.getModel()) + 1]; strcpy(model, other.getModel());
		category = new char[strlen(other.getCategory()) + 1]; strcpy(category, other.getCategory());
		price = other.getPrice();
		count = other.getCount();
		colour = new char[strlen(other.getColour()) + 1]; strcpy(colour, other.getColour());
		fabric = new char[strlen(other.getFabric()) + 1]; strcpy(fabric, other.getFabric());
		length = other.getLength();
}

Product& Product::operator=(Product const & other) {
	if (this != &other) {
		delete[] SKU;
		SKU = new char[strlen(other.getSku()) + 1]; strcpy(SKU, other.getSku());
		delete[] brand;
		brand = new char[strlen(other.getBrand()) + 1]; strcpy(brand, other.getBrand());
		delete[] model;
		model = new char[strlen(other.getModel()) + 1]; strcpy(model, other.getModel());
		delete[] category;
		category = new char[strlen(other.getCategory()) + 1]; strcpy(category, other.getCategory());
		price = other.getPrice();
		count = other.getCount();
		delete[] colour;
		colour = new char[strlen(other.getColour()) + 1]; strcpy(colour, other.getColour());
		delete[] fabric;
		fabric = new char[strlen(other.getFabric()) + 1]; strcpy(fabric, other.getFabric());
		length = other.getLength();
	}
	return *this;
}

Product::~Product() {
	delete[] SKU;
	delete[] brand;
	delete[] model;
	delete[] category;
	delete[] colour;
	delete[] fabric;
}

void Product::setSku(char* _SKU) {
	delete[] SKU;
	SKU = new char[strlen(_SKU) + 1]; strcpy(SKU, _SKU);
}

void Product::setBrand(char* _brand) {
	delete[] brand;
	brand = new char[strlen(_brand) + 1]; strcpy(brand, _brand);
}

void Product::setModel(char* _model) {
	delete[] model;
	model = new char[strlen(_model) + 1]; strcpy(model, _model);
}

void Product::setCategory(char* _category) {
	delete[] category;
	category = new char[strlen(_category) + 1]; strcpy(category, _category);
}

void Product::setPrice(double _price) {
	price = _price;
}

void Product::setCount(int _count) {
	count = _count;
}

void Product::setColour(char* _colour) {
	delete[] colour;
	colour = new char[strlen(_colour) + 1]; strcpy(colour, _colour);
}

void Product::setFabric(char* _fabric) {
	delete[] fabric;
	fabric = new char[strlen(_fabric) + 1]; strcpy(fabric, _fabric);
}

void Product::setLength(double _length) {
	length = _length;
}

char* Product::getSku()const {
	return SKU;
}

char* Product::getBrand()const {
	return brand;
}

char* Product::getModel()const {
	return model;
}

char* Product::getCategory()const {
	return category;
}

double Product::getPrice()const {
	return price;
}

int Product::getCount()const {
	return count;
}

char* Product::getColour()const {
	return colour;
}

char* Product::getFabric()const {
	return fabric;
}

double Product::getLength()const {
	return length;
}



