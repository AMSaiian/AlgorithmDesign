#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void createFirstFiles(string source);
void writeSeries(ofstream& receiver, ifstream& source);
void sort();
bool moreThanOneNotEmpty();
void mergingFiles(vector<ofstream>& receiver, vector<ifstream>& source, bool direction);
bool checkOrder();
