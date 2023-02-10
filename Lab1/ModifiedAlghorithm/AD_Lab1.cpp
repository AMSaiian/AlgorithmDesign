#include <iostream>
#include <fstream>
#include <string>
#include "fileProcessing.h"

using namespace std;

int main()
{
	createFirstFiles("file1gb.txt");
	mergingFiles();
	cout << "Is order correct?: " << boolalpha << checkOrder();
}
