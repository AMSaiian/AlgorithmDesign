#include <iostream>
#include <fstream>
#include <string>
#include "fileProcessing.h"

using namespace std;

int main()
{
	createFirstFiles("file.txt");
	sort();
	cout << "Is order correct?: " << boolalpha << checkOrder();
}

