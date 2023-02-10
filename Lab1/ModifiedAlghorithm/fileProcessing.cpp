#include "fileProcessing.h"
#define fileAmount 4

void createFirstFiles(string source)
{
	ifstream input(source, ios::binary);
	input.seekg(0, ios::beg);
	auto countAmountNums = [](ifstream& input)
	{
		input.seekg(0, ios::end);
		long long bytes = input.tellg();
		input.seekg(0, ios::beg);
		bytes /= sizeof(long);
		return bytes;
	};
	long numsAmount = countAmountNums(input);
	long amountForFile = numsAmount / fileAmount;
	long amountForLastFile = numsAmount - amountForFile * fileAmount + amountForFile;
	vector<long> tempForSort(amountForFile);
	vector<ofstream> auxiliary;
	string auxName = "";
	for (int i = 1; i <= fileAmount; i++)
	{
		auxName = "B" + to_string(i) + ".txt";
		auxiliary.push_back(ofstream(auxName, ios::binary));
	}
	auto getSortWriteNums = [&input, &tempForSort, &auxiliary](long amount, int auxNum)
	{
		input.read(reinterpret_cast<char*>(&tempForSort[0]), amount * sizeof(long));
		sort(tempForSort.begin(), tempForSort.end());
		auxiliary[auxNum].write(reinterpret_cast<char*>(&tempForSort[0]), amount * sizeof(long));
		tempForSort = vector<long>(amount);
	};
	for (int i = 0; i < fileAmount - 1; i++)
	{
		getSortWriteNums(amountForFile, i);
	}
	tempForSort.resize(amountForLastFile);
	getSortWriteNums(amountForLastFile, fileAmount - 1);
	input.close();
	for (int i = 0; i < fileAmount; i++)
	{
		auxiliary[i].close();
	}
}

void mergingFiles()
{
	vector<ifstream> auxiliary;
	string auxName = "";
	for (int i = 1; i <= fileAmount; i++)
	{
		auxName = "B" + to_string(i) + ".txt";
		auxiliary.push_back(ifstream(auxName, ios::binary));
		auxiliary[i - 1].seekg(0, ios::beg);
	}
	ofstream result("C.txt", ios::binary);
	vector<long> elements;
	auto checkEnd = [&elements]() 
	{
		for (auto elem : elements)
		{
			if (elem != numeric_limits<long>::max())
			{
				return false;
			}
		}
		return true;
	};
	auto getNum = [&auxiliary, &elements](int index)
	{
		if (auxiliary[index].eof())
			elements[index] = numeric_limits<long>::max();
		else
			auxiliary[index].read(reinterpret_cast<char*>(&elements[index]), sizeof(long));
	};
	long j = 0;
	elements = vector<long>(fileAmount, numeric_limits<long>::min());
	for (int i = 0; i < fileAmount; i++)
	{
		getNum(i);
	}
	do
	{
		long smaller = numeric_limits<long>::max();
		int indexSmaller = -1;
		for (int i = 0; i < fileAmount; i++)
		{
			if (elements[i] == numeric_limits<long>::max())
				continue;
			if (elements[i] < smaller)
			{
				smaller = elements[i];
				indexSmaller = i;
			}
		}
		if (indexSmaller != -1)
		{
			result.write(reinterpret_cast<char*>(&smaller), sizeof(long));
			getNum(indexSmaller);
		}
	} while (!checkEnd());
}

bool checkOrder()
{
	ifstream in("C.txt", ios::binary);
	in.seekg(0, ios::beg);
	long previous;
	long current;
	in.read(reinterpret_cast<char*>(&previous), sizeof(long));
	bool flag = true;
	while (!in.eof())
	{
		in.read(reinterpret_cast<char*>(&current), sizeof(long));
		if (current < previous)
		{
			flag = false;
			break;
		}
		previous = current;
	}
	return flag;
}
