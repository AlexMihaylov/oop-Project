#include "Controller.h"
#include <iostream>
#define MAX 1024

using namespace std;

Controller::Controller() {
	this->fileName = "solution.in"; //default
	this->size = 0;
	this->earnedMoney = 0.0;
	this->readSize = 0;
	this->finished = false;
	this->readFile(this->fileName);
};

bool Controller::isFinished() {
	return this->finished;
}

void Controller::setMainFile(char * fileName){ // proverka dali faila syshtestvuva
	this->fileName = fileName;
};

void Controller::printAllStocks() {
	for(int i = 0; i < this->size; i++) {
		this->elements[i]->print();
	}
};

void Controller::printEarnedMoney() {
	printf("Total earned money: %.2f .\n", this->earnedMoney);
};

Merchandise * Controller::findElementByName(char * name){
	for(int i = 0; i < this->size; i++) {
		if(strcmp(this->elements[i]->getName(), name) == 0){
			return this->elements[i];
		}
	}
	return NULL;
};

Merchandise * Controller::getElementsFromFile(char * fileName) {
	int T;
	char name[40];
	unsigned short number;
	float price;

	Merchandise *elements;

	FILE* stream = fopen(fileName, "r");
	fscanf(stream,"%d", &T);
	this->readSize = T;
	elements = new Merchandise[T];
	for(int i = 0; i < T; i++) {
		fscanf(stream, "%s %hd %f", &name, &number, &price);
		elements[i].setName(name);
		elements[i].setNumber(number);
		elements[i].setPrice(price);
	}
	fclose(stream);
	return elements;
};

void Controller::addElement(Merchandise newElement) {
	Merchandise * temp;
	temp = this->findElementByName(newElement.getName());
	if(temp == NULL) {
		this->elements[this->size] = new Merchandise(newElement);
		this->size++;
	} else {
		temp->setNumber(temp->getNumber() + newElement.getNumber());
		if(temp->getPrice() != newElement.getPrice()) {
			printf("Do you want to overwrite the price for %s %.2f with %.2f (y/n): ", temp->getName(), temp->getPrice() , newElement.getPrice());
			char c;
			fflush(stdin);
			scanf("%c", &c);
			if(c == 'y') temp->setPrice(newElement.getPrice());
		}
	}
};

void Controller::buyMerchandise(){
	char name[40];
	unsigned short number;

	printf("What merchandise do you want to buy? ");
	scanf("%s", &name);
	Merchandise * temp = this->findElementByName(name);
	if(temp == NULL){ printf("There is no such merchandise!\n"); return; }
	printf("How many of %s would you like to buy? ", temp->getName());
	scanf("%hd", &number);
	if(temp->getNumber() < number) { 
		printf("There are only %hd of %s left in stock!\n", temp->getNumber(), temp->getName()); 
		return; 
	}
	
	int num = number;
	int num2 = num/5;
	float price = temp->getPrice()*(num-num2);
	price += (temp->getPrice()*num2)/5;
	
	printf("Do you want to buy %hd of %s for %.2f? (y/n) ",number, temp->getName(), price);
	char c;
	fflush(stdin);
	scanf("%c",&c);
	if(c == 'y') {
		temp->setNumber(temp->getNumber() - number);
		this->earnedMoney = this->earnedMoney + price;
		temp->setSold(temp->getSold() + number);
	}
};

void Controller::printTopSeller() {
	int max = 0;
	char name[40];

	for(int i = 0;i < this->size; i++) {
		if(this->elements[i]->getSold() > max) { 
			max = this->elements[i]->getSold();
			strcpy_s(name, this->elements[i]->getName());
		}
	}
	if(max == 0) {
		printf("No product was sold today!\n");
	} else {
		Merchandise * temp = this->findElementByName(name);
		printf("Top seller for today is %s with %d sold items.\n",temp->getName(), temp->getSold());
	}
};

void Controller::menuHandler() {
	printf("\n----------------MENU----------------\n");
	printf("1 - List of all merchandises.\n");
	printf("2 - Total earned money.\n");
	printf("3 - Delete a merchandise by name.\n");
	printf("4 - Sorted list by prices.\n");
	printf("5 - Purchase by a product name.\n");
	printf("6 - Resupplying with merchandises.\n");
	printf("7 - Most sold item for \"today\".\n");
	printf("8 - Low supplied goods.\n");
	printf("9 - Rename a product.\n");
	printf("0 - Save and exit.\n");
	printf("Choose between 0-9: ");

	int option;
	fflush(stdin);
	scanf("%d",&option);
	system("CLS");
	switch(option){
	case 1: { this->printAllStocks(); return; }
	case 2: { this->printEarnedMoney(); return; }
	case 3: { this->deleteElement(); return; }
	case 4: { this->sort(); return; }
	case 5: { this->buyMerchandise(); return; }
	case 6: { this->readFile("new_stock.in"); return; }
	case 7: { this->printTopSeller(); return; }
	case 8: { this->printLowSupplied(); return; }
	case 9: { this->renameMerchandise(); return; }
	case 0: { this->saveAndExit(); return; }
	default: { printf("Invalid operation!\n"); return; }
	}
}

void Controller::printLowSupplied(){
	bool nothing = true;
	printf("Low supplied products are: \n");
	for(int i = 0; i < this->size; i++) {
		if(this->elements[i]->getNumber() < 5) {
			this->elements[i]->print();
			nothing = false;
		}
	}
	if(nothing) {
		printf("There are no low supplied products! \n");
	}
}

void Controller::renameMerchandise() {
	char name[40];
	printf("Enter a product name for renaming: ");
	scanf("%s",&name);
	
	Merchandise * temp = this->findElementByName(name);
	if(temp == NULL) {
		printf("Product %s was not found!\n", name);
	} else {
		printf("Enter new name: ");
		scanf("%s", &name);
		temp->setName(name);
	}
}

void Controller::saveAndExit() {
	FILE *stream = fopen("solution.in","w");
	fprintf(stream, "%d\n",this->size);
	for(int i = 0; i < this->size; i++) {
		fprintf(stream, "%s %hd %.2f\n", this->elements[i]->getName(),this->elements[i]->getNumber(),this->elements[i]->getPrice());
	}
	fclose(stream);
	this->finished = true;
}

void Controller::sort() {
	Merchandise * temp = new Merchandise[this->size];
	for(int i = 0; i < this->size; i++) {
		temp[i].setName(this->elements[i]->getName());
		temp[i].setPrice(this->elements[i]->getPrice());
		temp[i].setNumber(this->elements[i]->getNumber());
	}

	for(int i = 0; i < this->size; i++) {
		for(int j = this->size; j > i; j--) {
			if(temp[i].getPrice() < temp[j].getPrice()){
				Merchandise * c = new Merchandise(temp[i]);
				temp[i].setName(temp[j].getName());
				temp[i].setPrice(temp[j].getPrice());
				temp[i].setNumber(temp[j].getNumber());
				temp[j].setName(c->getName());
				temp[j].setPrice(c->getPrice());
				temp[j].setNumber(c->getNumber());
			}
		}
	}
	for(int i = 0; i < this->size; i++) {
		temp[i].print();
	}
}

void Controller::deleteElement() {
	char name[40];
	printf("Enter product name for delete: ");
	scanf("%s",&name);
	Merchandise * temp = this->findElementByName(name);
	if(temp == NULL) {
		printf("PRoduct %s does not exist!\n", name);
		return;
	}

	temp->setName(this->elements[this->size - 1]->getName());
	temp->setNumber(this->elements[this->size - 1]->getNumber());
	temp->setPrice(this->elements[this->size - 1]->getPrice());
	temp->setSold(this->elements[this->size - 1]->getSold());

	this->size = this->size-1;
};

void Controller::readFile(char * fileName) {
	Merchandise * elements = this->getElementsFromFile(fileName);
	for(int i = 0; i < this->readSize; i++) {
		this->addElement(elements[i]);
	}
};