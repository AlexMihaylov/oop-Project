#include "Merchandise.h"
#define MAX 4096


class Controller {
private:
	Merchandise * elements[MAX];
	char * fileName;
	int size;
	float earnedMoney;
	int readSize;
	bool finished;

	Merchandise * topSeller;
	Merchandise * findElementByName(char * name);
	Merchandise * getElementsFromFile(char * fileName);

	//user Interface functions
	void printAllStocks();
	void printEarnedMoney();
	void deleteElement();
	void sort();
	void buyMerchandise();
	void printTopSeller();
	void printLowSupplied();
	void renameMerchandise();
	void saveAndExit();

	//Auxiliary
	void readFile(char * fileName);
	void addElement(Merchandise newElement);

public:
	Controller();
	void setMainFile(char * name);
	void menuHandler();
	bool isFinished();
};