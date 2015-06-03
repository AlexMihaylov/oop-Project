#include "Merchandise.h"
#include <iostream>

using namespace std;

Merchandise::Merchandise() {
	strcpy_s(this->name, "");
	this->number = 0;
	this->price = 0;
	this->sold = 0;
}

Merchandise::Merchandise(char * name, unsigned short number, float price) {
	strcpy_s(this->name, name);
	this->price = price;
	this->number = number;
	this->sold = 0;
};

Merchandise::Merchandise(const Merchandise& newElement){
	strcpy_s(this->name, newElement.name);
	this->price = newElement.price;
	this->number = newElement.number;
	this->sold = newElement.sold;
}

void Merchandise::print() { //table view
	printf("%s(%d) : %10 %.2f lv.\n", this->name, this->number, this->price);
};

char * Merchandise::getName() {
	return this->name;
};

unsigned short Merchandise::getNumber() {
	return this->number;
};

float Merchandise::getPrice() {
	return this->price;
};

int Merchandise::getSold() {
	return this->sold;
};

void Merchandise::setName(char * name) {
	strcpy_s(this->name, name);
};

void Merchandise::setNumber(unsigned short number) {
	if(number < 0) printf("Broq ne moje da byde otricatelen!\n");
	else this->number = number;
};

void Merchandise::setPrice(float price){
	if(price < 0) printf("Cenata ne moje da byde otricatelna!\n");
	else this->price = price;
};

void Merchandise::setSold(int sold) {
	this->sold += sold;
}