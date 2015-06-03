#include <cstdio>
#include <iostream>
#include "Controller.h"

using namespace std;

int main() {
	Controller * mainController = new Controller();
	mainController->setMainFile("solution.in");

	while(!mainController->isFinished()) {
		system("PAUSE");
		system("CLS");
		mainController->menuHandler();
	}
	return 0;
}